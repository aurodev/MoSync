/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/**
 * @file Example_using_multiset.cpp
 * @author Gabriela Rata
 */

#include <assert.h>
#include <set>
#include <utility>  		//for std::pair
#include "../STLMoblet.h"
#include "../LOG.h"


void STLMoblet::STL_multiset()
{
	LOG("\n");
	LOG("========================= multiset ==============================================================================\n");
	LOG("/**");
	LOG(" * std::multiset is an associative container. Associative container means that,");
	LOG(" * the index doesn't have to be an integer. It can be any type. std::multiset has, as its first template parameter,");
	LOG(" * the index type, like this:");
	LOG(" * 			template <	class Key,");
	LOG(" * 					class Compare = less<Key>,");
	LOG(" * 					....");
	LOG("           	    	  > class multiset;");
	LOG(" * std::multiset sorts automatically it's elements from lower to higher. The second template parameter is");
	LOG(" * the ordering criterion, and  is by default std::less<Key>. Another ordering criterion can be provided, and it has to be");
	LOG(" * a class that takes two arguments of the same type as the container elements, and returns a bool. (See  example bellow).");
	LOG(" * std::multiset accepts multiple copies of an object.");
	LOG(" * std::multiset has bidirectional iterators. We can advance with ++ and -- operators, but we can't move more than one step.");
	LOG(" * That means that we can write for example:");
	LOG(" * 				++myMultisetIterator; 	//ok. Move one step forward");
	LOG(" * 				--myMultisetIterator; 	//ok. Move one step backward");
	LOG(" * 				myMultisetIterator + 5; //not ok. It won't compile. Only random access iterators can move more then a step");
	LOG(" * 				myMultisetIterator - 2	//not ok. It won't compile.");
	LOG(" * std::multiset is designed to be efficient accessing its elements.");
	LOG(" * std::multiset is defined in the <set> header");
	LOG(" */");

	using std::multiset;

	LOG("\n");
	LOG("/**");
	LOG(" * default constructor");
	LOG(" * We use the default comparison class, std::less, so it will sort the elements from the lower to the higher.");
	LOG(" */");
	TRACE(multiset<int> s1;);

	LOG("\n");
	LOG("/**");
	LOG("* empty function: returns true if the multiset contains no elements");
	LOG("*/");
	bool e = s1.empty();
	log_to_console(e, "bool e = s1.empty();	//e = ");

	LOG("\n");
	LOG("/**");
	LOG("* size function: returns the number of elements");
	LOG("*/");
	int sz = s1.size();
	log_to_console(sz, "int sz = s1.size();	//sz = ");

	LOG("\n");
	LOG("/**");
	LOG("* begin: returns an iterator referring to the first element.");
	LOG("* If the container is empty, it will return the one past-the-end element in the container,");
	LOG("* like the multiset::end() function. See bellow.");
	LOG("*/");
	TRACE(std::multiset<int>::iterator itBegin = s1.begin();)

	LOG("\n");
	LOG("/**");
	LOG("* end: returns an iterator referring to the one past-the-end element in the container.");
	LOG("* We must not deference the iterator returned by multiset::end(). It is used only to see is if we reached the");
	LOG("* end of the container, when we iterate through it.");
	LOG("*/");

	TRACE(std::multiset<int>::iterator itEnd = s1.end(););
	LOG("//the s1 multiset is empty, so s1.begin() will return the same value as multiset::end()");
	TRACE(assert(itBegin == itEnd););

	LOG( "\n");
	LOG( "/**");
	LOG( " * insert function: inserts an element in multiset, at the right place, so that all the elements are in a sorted order.");
	LOG( " */");

	s1.insert(20);
	log_to_console(s1, "s1.insert(20);	//s1 will contain: ");

	LOG("\n");
	s1.insert(3);
	log_to_console(s1, "s1.insert(3);	//s1 will contain: ");	//s1 will place 3 before 20.

	LOG("\n");
	s1.insert(55);
	log_to_console(s1, "s1.insert(55);	//s1 contains: "); //s1 will place 55 at the end, as it has the biggest value

	LOG("\n");
	s1.insert(4);   				//s1 will place 4 after 3
	log_to_console(s1, "s1.insert(4);	//s1 will contain: ");

	LOG("\n");
	s1.insert(3);
	log_to_console(s1, "s1.insert(3);	//s1 will contain: ");

	LOG("\n");
	s1.insert(3);
	log_to_console(s1, "s1.insert(3);	//s1 will contain: ");


	LOG("\n");
	LOG("/**");
	LOG(" * insert function: inserts a range of elements in multiset");
	LOG(" * We can use another multiset to add elements to our multiset, or we can use any container (or array), that");
	LOG(" * provides a way to iterate through it.");
	LOG(" */");
	LOG("\n");

	int array[] = { 20, 10, 15, 10 };
	LOG("int array[] = { 20, 10, 15, 10 };");
	TRACE(int arraySize = sizeof(array)/sizeof(array[0]););
	s1.insert(array, array + arraySize);
	log_to_console(s1, "s1.insert(array, array + arraySize);	//s1 will contain: ");

	LOG("\n");
	TRACE(multiset<int> s1_1;);
	s1_1.insert(s1.begin(), s1.end());
	log_to_console(s1_1, "s1_1.insert(s1.begin(), s1.end());		//s1_1 will contain: ");

	LOG("\n");
	LOG("/**");
	LOG(" * default constructor");
	LOG(" * The second template parameter, \"LessExperienceFunctor\", is the comparison class. The std::multiset object will use");
	LOG(" * an object of type \"LessExperienceFunctor\" to compare objects of type \"Employee\" and to sort them accordingly.");
	LOG(" * The sorting is made as we insert elements, so in every moment the elements in a std::multiset are sorted.");
	LOG(" */");
	LOG("\n");

	multiset<Employee, LessExperienceFunctor> s2;
	LOG("multiset<Employee, LessExperienceFunctor> s2;");

	TRACE(Employee middle(5, "Phil");)
	TRACE(Employee senior(7, "Bil"););
	TRACE(Employee junior1(1, "Tim"););
	TRACE(Employee junior2(1, "Jim"););

	LOG("\n");
	s2.insert(senior);
	log_to_console(s2, "s2.insert(senior); 	//s2 will contain: ");

	LOG("\n");
	s2.insert(middle);
	log_to_console(s2, "s2.insert(middle);	//s1 will contain: ");

	LOG("\n");
	s2.insert(junior1);
	log_to_console(s2, "s2.insert(junior1);	//s2 will contain: ");

	LOG("\n");
	s2.insert(junior1);
	log_to_console(s2, "s2.insert(junior1);	//s2 will contain: ");

	LOG("\n");
	LOG("/**");
	LOG(" * constructor");
	LOG(" * Iterates between the first and the second iterator (that are provided as parameters),");
	LOG(" * and makes a copy of each of the elements from that range, inserting it into the container.");
	LOG(" * In the example bellow, a the new multiset is constructed and is filled with the all elements from the s2 set.");
	LOG(" */");

	multiset<Employee,  LessExperienceFunctor> s3(s2.begin(), s2.end());
	log_to_console(s3, "multiset<Employee,  LessExperienceFunctor> s3(s2.begin(), s2.end());	//s3 will contain:");

	LOG("\n");
	LOG("//multiset overloads the following operators: ==, !=, <, >, <=, >=");
	TRACE(assert( s3 == s2 ););

	LOG("\n");
	LOG("/**");
	LOG(" * copy constructor");
	LOG(" */");

	multiset<Employee,  LessExperienceFunctor> s4(s3);

	log_to_console("multiset<Employee,  LessExperienceFunctor> s4(s3);");
	TRACE(assert( s4 == s3 ););

	LOG("\n");
	LOG("/**");
	LOG(" *  erase function: removes elements. It will remove all the elements with the specified value.");
	LOG(" */");
	LOG("\n");

	multiset<Employee,  LessExperienceFunctor>::iterator it = s4.begin();

	log_to_console(*it, "multiset<Employee,  LessExperienceFunctor>::iterator it = s4.begin();	//*it = ");

	LOG("\n");
	TRACE(s4.erase(junior1););
	LOG("//\"it\" iterator was invalidated by the erase. We want to retrieve the first element, so we call a");
	it = s4.begin();
	log_to_console(*it, "it = s4.begin();	//*it = ");

	LOG("\n");
	s4.erase(s4.begin(), s4.end());
	LOG("s4.erase(s4.begin(), s4.end());	//erase all the elements");

	sz = s4.size();
	log_to_console(sz, "sz = s4.size();	//sz = ");

	LOG("\n");
	LOG("/**");
	LOG(" * clear function: all the elements are destroyed and removed from the set.");
	LOG(" * After calling this function the multiset will have the size zero.");
	LOG(" */");

	TRACE(s3.clear(););
	TRACE(assert(s3.size() == 0););

	LOG("\n");
	LOG("/**");
	LOG(" * find function: Searches the container for an element and returns an iterator to it if found.");
	LOG(" * The function returns an iterator to one of the elements with that value, even if there are more than one");
	LOG(" * elements having that value. To get all the elements use multiset::equal_range.");
	LOG(" * If it doesn't find an element it returns an iterator to the element past the end of the container (set::end).");
	LOG(" * multiset::find() member function is much faster than the generic std::find( ) algorithm (from <algorithm>).");
	LOG(" */");

	multiset<Employee,  LessExperienceFunctor>::iterator found = s3.find(junior1);
	LOG("multiset<Employee,  LessExperienceFunctor>::iterator found = s3.find(junior1);");
	TRACE(assert(s3.end() == found););

	LOG("\n");
	TRACE(Employee firstE(1, "Bob"););
	TRACE(Employee secondE(1, "Alex"););

	LOG("\n");
	TRACE(s3.insert(firstE););
	s3.insert(secondE);
	log_to_console(s3, "s3.insert(secondE);	//s3 contains: ");

	LOG("\n");
	Employee findMe(1);
	LOG("Employee findMe(1);");

	found = s3.find(findMe);

	log_to_console(*found, "found = s3.find(findMe);	//*found = ");

	LOG("\n");
	LOG("/**");
	LOG(" * lower_bound: Returns an iterator referring to the first element in the container which is not");
	LOG(" * less (using the container's comparison object) than the value provided as parameter.");
	LOG(" */");
	LOG("\n");

	int a[] = { 3, 5, 1, 7, 3, 3 };
	LOG("int a[] = { 3, 5, 1, 7, 3, 3 };");
	TRACE(int aSize = sizeof(a)/sizeof(a[0]););

	LOG("\n");
	multiset<int> s5(a, a + aSize);
	log_to_console(s5, "multiset<int> s5(a, a + aSize); 	//s5 will contain: ");

	LOG("\n");
	multiset<int>::iterator lowerBound = s5.lower_bound(3);  //returns 3 (the first element >= 3)
	log_to_console(*lowerBound, "multiset<int>::iterator lowerBound = s5.lower_bound(3);	"
			"//returns the first element >= 3 => *lowerBound = ");

	LOG("\n");
	--lowerBound;
	log_to_console(*lowerBound, "--lowerBound; //*lowerBound = ");

	LOG("\n");
	LOG("/**");
	LOG(" * upper_bound: Returns an iterator pointing to the first element in the container which compares");
	LOG(" * strictly greater than the value provided as argument (using the container's comparison object).");
	LOG(" */");
	multiset<int>::iterator upperBound = s5.upper_bound(3);
	log_to_console(*upperBound, "multiset<int>::iterator upperBound = s5.upper_bound(3); 	//returns the first elem >3 => *upperBound = ");

	LOG("\n");
	LOG("/**");
	LOG(" * equal_range:");
	LOG(" * prototype: pair<iterator, iterator> equal_range ( const key_type &someKey ) const;");
	LOG(" * Returns the bounds of a range that includes all the elements in the container with a");
	LOG(" * key that compares equal to \"someKey\".");
	LOG(" * If \"someKey\" does not match any key in the container, the range returned has a length of zero,");
	LOG(" * with both iterators pointing to the nearest value greater than \"someKey\",");
	LOG(" * If \"someKey\" is the greater than all the elements  set::end is returned.");
	LOG(" */");
	LOG("\n");

	std::pair< multiset<int>::iterator, multiset<int>::iterator > equal = s5.equal_range(3);
	LOG("std::pair< multiset<int>::iterator, multiset<int>::iterator > equal = s5.equal_range(3);");

	log_to_console(*equal.first, "//equal.first = ");
	log_to_console(*equal.second, "//equal.second = ");

	LOG("\n");
}
