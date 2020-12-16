/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_map_og.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:47:25 by rofernan          #+#    #+#             */
/*   Updated: 2020/12/12 18:47:27 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

template <class S, class T>
void	print_cap(std::map<S, T> mp)
{
	std::cout << "mp.size():\t" << mp.size() << std::endl;
	std::cout << "mp.max_size():\t" << mp.max_size() << std::endl;
	std::cout << "mp.empty():\t" << mp.empty() << std::endl;
	std::cout << std::endl;
}

template <class S, class T>
void	print_content(std::map<S, T> mp)
{
	std::cout << "print content with operator[]:\n";
	for (S i = 0; i < mp.size(); i++)
		std::cout << "vec[" << i << "]: " << mp[i] << std::endl;
	std::cout << std::endl;
}

template <class S, class T>
void	print_content_iterator(std::map<S, T> mp)
{
	std::cout << "print content with iterarors:\n";
	for (typename std::map<S, T>::iterator it = mp.begin(); it != mp.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << std::endl;
}

template <class S, class T>
void	print_reverse_iterator(std::map<S, T> mp)
{
	std::cout << "print content with reverse iterarors:\n";
	for (typename std::map<S, T>::reverse_iterator it = mp.rbegin(); it != mp.rend(); it++)
		std::cout << "*it:\t" << *it << std::endl;
	std::cout << std::endl;
}

int main(void)
{
	std::cout << "################# TESTS ORIGINAL MAP #################" << std::endl;

	std::map<std::string, int> mp;
	// std::map<std::string, int>::iterator it = mp.begin();
	// std::map<std::string, int>::iterator it2 = mp.begin();

	print_cap(mp);
	// print_content_iterator(mp);

	// mp["aa"] = 4;
	// mp["al"] = 2;
	// mp["ab"] = 8;
	std::cout << "********** MP INSERT **********" << std::endl;
	mp.insert(std::make_pair("l", 10));
	std::cout << mp["l"] << std::endl;
	std::cout << mp["b"] << std::endl;
	mp["a"] = 4;
	mp["q"] = 2;
	mp["i"] = 8;
	mp["p"] = mp["a"];
	mp["o"] = 15;
	std::cout << "insert: " << mp.insert(mp.begin(), std::make_pair("m", 100))->first << std::endl;;

	// mp.print();

	print_cap(mp);
	print_content_iterator(mp);

	// mp.erase("q");
	// mp.erase("b");
	// mp.erase("a");
	// mp.erase("i");
	// std::cout << "erase: " << mp.erase("l") << std::endl;
	// mp.erase(mp.begin());
	// mp.erase(mp.begin(), mp.end());
	// mp.erase("p");
	// mp.erase("a");
	// mp.erase("l");
	// mp.erase("o");
	// mp.clear();
	// std::map<std::string, int>::iterator it = mp.begin();
	// it++;
	// it++;
	// it = mp.end();
	// it--;
	// mp.erase(it);
	// // mp = mp2;
	
	// // mp.print();

	// print_cap(mp);
	// print_content_iterator(mp);

	// std::map<char,int> mymap;
	// std::map<char,int>::iterator itlow,itup;

	// mymap['a']=20;
	// mymap['d']=80;
	// mymap['e']=100;
	// mymap['g']=100;
	// mymap['i']=100;
	// mymap['r']=100;
	// mymap['u']=100;


	// itlow=mymap.lower_bound ('b');  // itlow points to b
	// itup=mymap.upper_bound ('s');   // itup points to e (not d!)	
	// print_content_iterator(mymap);
	// mymap.erase(itlow,itup);        // erases [itlow,itup)


	// // print_cap(mymap);
	// // print_content_iterator(mymap);

	// for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << '\n';


	// std::pair<std::map<char,int>::iterator, std::map<char,int>::iterator> ret;
	// ret = mymap.equal_range('b');
	// std::cout << "lower bound points to: ";
	// std::cout << ret.first->first << " => " << ret.first->second << '\n';	
	// std::cout << "upper bound points to: ";
	// std::cout << ret.second->first << " => " << ret.second->second << '\n';

    return (0);
}
