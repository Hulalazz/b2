//This file is part of Bertini 2.
//
//python/generic_observers.cpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//python/generic_observers.cpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with python/generic_observers.cpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2017 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
//
//  Dani Brake
//  UWEC
//  Fall 2017
//
//
//  python/generic_observers.cpp:  source file for exposing trackers to python.


#include "generic_observer.hpp"

namespace bertini{
	namespace python{

		// Wrapper struct to allow derived classes to overide methods in python
		struct ObserverWrapper : AnyObserver, wrapper<AnyObserver>
		{

			void Observe(AnyEvent const& e) { this->get_override("Observe")(e);}
			
		}; // re: ObserverWrapper


		void ExportObserver()
		{
			// scope current_scope;
			// std::string new_submodule_name(extract<const char*>(current_scope.attr("__name__")));
			// new_submodule_name.append(".symbol");
			// object new_submodule(borrowed(PyImport_AddModule(new_submodule_name.c_str())));
			// current_scope.attr("symbol") = new_submodule;

			// scope new_submodule_scope = new_submodule;

			class_<ObserverWrapper, boost::noncopyable>("AbstractObserver", no_init)
			// .def(NodeVisitor<Node>())
			;
		}
}} // namespaces
