#include <iostream>
#include <tuple>

void adjust_values(double* alpha1, double* beta1, double* alpha2, double* beta2)
{
	*alpha1 *= 2;
	*beta1 *= 2;
	*alpha2 *= 2;
	*beta2 *= 2;
}

void adjust_values2(double* alpha1, double* beta1, double* alpha2, double* beta2, double* alpha3, double* beta3)
{

}

using location = double;
using mytime = double;

// A class from our distributed computation system that 
// accesses the alpha and beta values.
class reading
{
public:
	double alpha_value(location l, mytime t) const
	{
		return l * t;
	}

	double beta_value(location l, mytime t) const
	{
		return l / t;
	}
};

template <std::size_t FunctionIndex, typename FunctionsTuple, typename Params, std::size_t... I>
	auto dispatch_params(FunctionsTuple & functions, Params & params, std::index_sequence<I...>)
{
	return (std::get<FunctionIndex>(functions)) (std::get<I>(params)...);
}

template <typename FunctionsTuple, std::size_t... I, typename Params, typename ParamsSeq>
	auto dispatch_functions(FunctionsTuple & functions, std::index_sequence<I...>, Params & params, ParamsSeq params_seq)
{
	return std::make_tuple(dispatch_params<I>(functions, params, params_seq)...);
}

template <typename F, typename Tuple, std::size_t... I>
void dispatch_to_c(F f, Tuple & t, std::index_sequence<I...>)
{
	f(&std::get<I>(t)...);
}

template <typename LegacyFunction, typename... Functions, typename... Params>
auto magic_wand(LegacyFunction legacy,
		const std::tuple<Functions...> & functions,
		const std::tuple<Params...> & params1,
		const std::tuple<Params...> & params2)
{
	static const std::size_t functions_count = sizeof...(Functions);
	static const std::size_t params_count = sizeof...(Params);

	auto params = std::tuple_cat(
		dispatch_functions(functions, std::make_index_sequence<functions_count>(), params1, std::make_index_sequence<params_count>()),
		dispatch_functions(functions, std::make_index_sequence<functions_count>(), params2, std::make_index_sequence<params_count>())
	);

	static constexpr auto t_count = std::tuple_size<decltype(params)>::value;

	dispatch_to_c(legacy, params, std::make_index_sequence<t_count>());

	return params;
}

template <typename Reading>
std::tuple<double, double, double, double>
get_adjusted_values(Reading& r, location l, mytime t1, mytime t2)
{
	return magic_wand(adjust_values,
                      std::make_tuple([&r](double l, double t) { return r.alpha_value(l, t); },
                                      [&r](double l, double t) { return r.beta_value(l, t); }),
                      std::make_tuple(l, t1),
                      std::make_tuple(l, t2));
}


template <typename Reading, typename Function>
std::tuple<double, double, double, double>
get_adjusted_values(Reading& r, Function& f, location l, mytime t1, mytime t2)
{
	return magic_wand(f,
                      std::make_tuple([&r](double l, double t) { return r.alpha_value(l, t); },
                                      [&r](double l, double t) { return r.beta_value(l, t); }),
                                      [&r](double l, double t) { return r.beta_value(l, t); }),
                      std::make_tuple(l, t1),
                      std::make_tuple(l, t2),
                      std::make_tuple(l, t2));
}

int main()
{
	reading r;
	location l = 5;
	mytime t1 = 10;
	mytime t2 = 15;

	//auto result = get_adjusted_values(r, l, t1, t2);
	auto result = get_adjusted_values(r, adjust_values, l, t1, t2);
	auto result2 = get_adjusted_values(r, adjust_values2, l, t1, t2);
	std::cout << "Adjusted alpha1: " << std::get<0>(result) << std::endl;
	std::cout << "Adjusted beta1: " << std::get<1>(result) << std::endl;
	std::cout << "Adjusted alpha2: " << std::get<2>(result) << std::endl;
	std::cout << "Adjusted beta2: " << std::get<3>(result) << std::endl;
}

