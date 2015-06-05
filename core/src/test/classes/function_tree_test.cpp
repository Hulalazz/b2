//This file is part of Bertini 2.0.
//
//function_tree_test.cpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//function_tree_test.cpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with function_tree_test.cpp.  If not, see <http://www.gnu.org/licenses/>.
//

//  function_tree_test.cpp
//
//  Created by Collins, James B. on 4/30/15.
//  Copyright (c) 2015 West Texas A&M University. All rights reserved.
//
// also modified by
//  Daniel Brake
//  University of Notre Dame
//  ACMS
//  Spring, Summer 2015

#include <cmath>
#include <iostream>
#include <vector>

#include "bertini.hpp"
#include "function_tree.hpp"


#include <boost/spirit/include/qi.hpp>



#include <boost/test/unit_test.hpp>


using Variable = bertini::Variable;
using Node = bertini::Node;


BOOST_AUTO_TEST_SUITE(function_tree_class)

/////////// Basic Operations Alone ///////////////////

BOOST_AUTO_TEST_CASE(manual_construction_num_squared){
    using mpfr_float = boost::multiprecision::mpfr_float;

    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    std::shared_ptr<Node> N = a;
    
    N *= N;
        
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-19.80)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (38.08)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-19.80")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("38.08")) < 1e-15);
    
}


BOOST_AUTO_TEST_CASE(manual_construction_x_squared){
    using mpfr_float = boost::multiprecision::mpfr_float;

	std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
	
	std::shared_ptr<Node> N = x;

	N *= N;
    
    x->set_current_value<dbl>(std::complex<double>(3.1, 4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1", "4.1"));
	

    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-7.20)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (25.42)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-7.20")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("25.42")) < 1e-15);
	
}


BOOST_AUTO_TEST_CASE(manual_construction_sqrt_x){
    using mpfr_float = boost::multiprecision::mpfr_float;

	std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
	
	std::shared_ptr<Node> N = pow(x, 1.0/2);
	
    x->set_current_value<dbl>(std::complex<double>(3.1, 4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1", "4.1"));
	
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (2.02978310545222525193724454915    )) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (1.00996012553926077130365939509)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("2.02978310545222525193724454915")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("1.00996012553926077130365939509")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_x_plus_y_plus_number){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");

    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = x+y+a;
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - 15.3) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - 19.6) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("19.6")) < 1e-15);
    
    N = a+x+y;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - 15.3) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - 19.6) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("19.6")) < 1e-15);
    
    N = y+a+x;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - 15.3) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - 19.6) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("19.6")) < 1e-15);

    
    N = y+x+a;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - 15.3) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - 19.6) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("19.6")) < 1e-15);

    
    N = x+a+y;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - 15.3) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - 19.6) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("19.6")) < 1e-15);

    N = a+y+x;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - 15.3) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - 19.6) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("19.6")) < 1e-15);

}


BOOST_AUTO_TEST_CASE(manual_construction_x_minus_y_minus_number){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = x-y-a;
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-9.1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-11.4)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-9.1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-11.4")) < 1e-15);
    
    N = x-a-y;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-9.1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-11.4)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-9.1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-11.4")) < 1e-15);
    
}


BOOST_AUTO_TEST_CASE(manual_construction_x_times_y_times_number){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = x*y*a;
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("152.482")) < 1e-15);
    
    N = a*x*y;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("152.482")) < 1e-15);
    
    N = y*a*x;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("152.482")) < 1e-15);
    
    
    N = y*x*a;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("152.482")) < 1e-15);
    
    
    N = x*a*y;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("152.482")) < 1e-15);
    
    N = a*y*x;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("152.482")) < 1e-15);
    
}


BOOST_AUTO_TEST_CASE(manual_construction_x_divide_y){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = x/y;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (0.386833855799373040752351097179)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (0.0307210031347962382445141065831)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("0.386833855799373040752351097179")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("0.0307210031347962382445141065831")) < 1e-15);
    
    N = y/x;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (2.56888720666161998485995457986)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-.204012112036336109008327024981)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("2.56888720666161998485995457986")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-.204012112036336109008327024981")) < 1e-15);
    
}


BOOST_AUTO_TEST_CASE(manual_construction_negate_x){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = -x;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-3.1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-4.1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-3.1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-4.1")) < 1e-15);
}







/////////// Basic Operations Combined ///////////////////


BOOST_AUTO_TEST_CASE(manual_construction_lx_plus_y_plus_num1l_pow_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = pow(x+y+a,p);
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (1.47373859861011906752915834413)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (61.1940146700680549277802310549)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("1.47373859861011906752915834413")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("61.1940146700680549277802310549")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_lx_minus_y_minus_num1l_pow_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = pow(x-y-a,p);
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (0.187521616923652701788257060900)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-0.128781676888908238758111616834e-1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("0.187521616923652701788257060900")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-0.128781676888908238758111616834e-1")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_lx_times_y_times_num1l_pow_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    
    std::shared_ptr<Node> N = pow(x*y*a,p);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-4233.03175646421208461558542114)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-14580.7052867789482445998485069)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-4233.03175646421208461558542114")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-14580.7052867789482445998485069")) < 1e-15);
    
    N = pow(x,p)*pow(y,p)*pow(a,p);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-4233.03175646421208461558542114)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-14580.7052867789482445998485069)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-4233.03175646421208461558542114")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-14580.7052867789482445998485069")) < 1e-15);

}


BOOST_AUTO_TEST_CASE(manual_construction_lx_over_yl_pow_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = pow(x/y,p);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-0.545556158382074857806127460034e-1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (0.533784190973489480675492333410)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-0.545556158382074857806127460034e-1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("0.533784190973489480675492333410")) < 1e-15);
    
    N = pow(x,p)/pow(y,p);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-0.545556158382074857806127460034e-1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (0.533784190973489480675492333410)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-0.545556158382074857806127460034e-1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("0.533784190973489480675492333410")) < 1e-15);

}


BOOST_AUTO_TEST_CASE(manual_construction_lnegative_xl_pow_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = -x;
    N = pow(N,p);
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-0.131587899902263949870593203575e-1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (0.0843055961727772006281440933177)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-0.131587899902263949870593203575e-1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("0.0843055961727772006281440933177")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_negate_x_plus_y_plus_num1){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = -(x+y+a);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-15.3)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-19.6)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-19.6")) < 1e-15);
    
    N = -x-y-a;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-15.3)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-19.6)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-15.3")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-19.6")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_negate_x_minus_y_minus_num1){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = -(x-y-a);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (9.1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (11.4)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("9.1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("11.4")) < 1e-15);
    
    N = -x+y+a;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (9.1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (11.4)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("9.1")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("11.4")) < 1e-15);

}



BOOST_AUTO_TEST_CASE(manual_construction_negate_x_times_y_times_num1){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = -(x*y*a);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-152.482")) < 1e-15);
    
    N = (-x)*y*a;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-152.482")) < 1e-15);

    N = x*(-y)*a;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-152.482")) < 1e-15);

    N = x*y*(-a);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (419.166)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-152.482)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("419.166")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-152.482")) < 1e-15);

}



BOOST_AUTO_TEST_CASE(manual_construction_negate_x_over_y){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = -(x/y);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-0.386833855799373040752351097179)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-0.0307210031347962382445141065831)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-0.386833855799373040752351097179")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-0.0307210031347962382445141065831")) < 1e-15);
    
    N = -x/y;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-0.386833855799373040752351097179)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-0.0307210031347962382445141065831)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-0.386833855799373040752351097179")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-0.0307210031347962382445141065831")) < 1e-15);

    N = x/(-y);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-0.386833855799373040752351097179)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-0.0307210031347962382445141065831)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-0.386833855799373040752351097179")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-0.0307210031347962382445141065831")) < 1e-15);

}


BOOST_AUTO_TEST_CASE(manual_construction_negate_x_pow_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = pow(x,p);
    N = -N;
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (8.11853389158295779816789463958)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (15.8454958754113708210851923835)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("8.11853389158295779816789463958")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("15.8454958754113708210851923835")) < 1e-15);
}







/////////// Order of Operations ///////////////////

BOOST_AUTO_TEST_CASE(manual_construction_x_times_y_over_num){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = x*y/a;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (7.65745573159366262814538676608)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (7.02595526561043802423112767940)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("7.65745573159366262814538676608")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("7.02595526561043802423112767940")) < 1e-15);
    
}


BOOST_AUTO_TEST_CASE(manual_construction_lx_plus_num1l_times_ly_plus_num2l){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> b = std::make_shared<Number>("-0.2", "-2.1");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = (x+a)*(y+b);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-19.76)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (134.12)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-19.76")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("134.12")) < 1e-15);
    
}


BOOST_AUTO_TEST_CASE(manual_construction_x_plus_num1_times_y_plus_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> b = std::make_shared<Number>("-0.2", "-2.1");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = x+a*y+b;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-22.62)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (84.94)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-22.62")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("84.94")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_lx_plus_num1l_over_ly_plus_num2l){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> b = std::make_shared<Number>("-0.2", "-2.1");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = (x+a)/(y+b);
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (0.975964391691394658753709198813)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (0.242729970326409495548961424332)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("0.975964391691394658753709198813")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("0.242729970326409495548961424332")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_x_plus_num1_over_y_plus_num2){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Variable> y = std::make_shared<Variable>("y");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> b = std::make_shared<Number>("-0.2", "-2.1");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    y->set_current_value<dbl>(std::complex<double>(8.8,9.9));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    y->set_current_value<mpfr>(bertini::complex("8.8","9.9"));
    
    std::shared_ptr<Node> N = x+a/y+b;
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (3.38652037617554858934169278997)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (2.08902821316614420062695924765)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("3.38652037617554858934169278997")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("2.08902821316614420062695924765")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_lx_pow_num2l_plus_num1){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = pow(x,p)+a;
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-4.71853389158295779816789463958)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-10.2454958754113708210851923835)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-4.71853389158295779816789463958")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-10.2454958754113708210851923835")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_x_plus_lnum1_pow_num2l){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = x+pow(a,p);
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-15.4166456956270315541897576762)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-13.7214237196743288610978812983)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-15.4166456956270315541897576762")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-13.7214237196743288610978812983")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_x_times_lnum1_pow_num2l){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = x*pow(a,p);
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (15.6662355942209505125130645268)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-131.164660883061248841581438497)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("15.6662355942209505125130645268")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-131.164660883061248841581438497")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_lx_pow_num2l_times_num1){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = pow(x,p)*a;
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (61.1317616709216200843062355730)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-99.3384757692632244614298640855)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("61.1317616709216200843062355730")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-99.3384757692632244614298640855")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_lx_pow_num2l_over_num1){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = pow(x,p)/a;
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-2.71057297608773842292283129362)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-.195966826270598721387452099773)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-2.71057297608773842292283129362")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-.195966826270598721387452099773")) < 1e-15);
}


BOOST_AUTO_TEST_CASE(manual_construction_x_over_lnum1_pow_num2l){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Variable> x = std::make_shared<Variable>("x");
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    std::shared_ptr<Number> p = std::make_shared<Number>("0.8", "-1.7");
    
    x->set_current_value<dbl>(std::complex<double>(3.1,4.1));
    x->set_current_value<mpfr>(bertini::complex("3.1","4.1"));
    
    std::shared_ptr<Node> N = x/pow(a,p);
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-.197540501416155894924318155219)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-0.312987045273878751347728847903e-1)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-.197540501416155894924318155219")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-0.312987045273878751347728847903e-1")) < 1e-15);
}











/////////// Special Functions ///////////////////
BOOST_AUTO_TEST_CASE(manual_construction_sin_num){
    using mpfr_float = boost::multiprecision::mpfr_float;
    
    std::shared_ptr<Number> a = std::make_shared<Number>("3.4", "5.6");
    
    std::shared_ptr<Node> N = sin(a);
    
    BOOST_CHECK(abs(N->Eval<dbl>().real() - (-34.5530035635025892859584920916)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<dbl>().imag() - (-130.722093418701896942083255318)) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().real() - mpfr_float("-34.5530035635025892859584920916")) < 1e-15);
    BOOST_CHECK(abs(N->Eval<mpfr>().imag() - mpfr_float("-130.722093418701896942083255318")) < 1e-15);
}




BOOST_AUTO_TEST_SUITE_END()
