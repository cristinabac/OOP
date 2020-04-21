#include "dynamicVector.h"
#include "Dog.h"
#include "Repo.h"
#include "Controller.h"
#include "Ui.h"
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


/*
void initialize_repo(Repo &r)
{
	r.add_dog(Dog{ "labrador","Max",7,"https://dogtime.com/dog-breeds/labrador-retriever#/slide/1" });
	r.add_dog(Dog{ "beagle","Rex",8,"https://dogtime.com/dog-breeds/beagle#/slide/1" });
	r.add_dog(Dog{ "basenji","Jeff",3,"https://dogtime.com/dog-breeds/basenji#/slide/1" });
	r.add_dog(Dog{ "bichon","Pufi",6,"link//blabla" });
	r.add_dog(Dog{ "labrador","Lola",10,"link//blabla" });
	r.add_dog(Dog{ "samoyed","Kiki",2,"link//blabla" });
	r.add_dog(Dog{ "labrador","Joe",4,"link//blabla" });
	r.add_dog(Dog{ "chihuahua","Maxim",3,"link//blabla" });
	r.add_dog(Dog{ "labrador","Roger",1,"link//blabla" });
	r.add_dog(Dog{ "labrador","Sisi",2,"link//blabla" });
	r.add_dog(Dog{ "labrador","Marcel",6,"link//blabla" });
}


void test_repo()
{
	Repo r{};
	Dog d{ "labrador","Max",7,"link//blabla" };
	Dog d2{ "golden","Rex",6,"link2" };
	r.add_dog(d);
	r.add_dog(d2);

	assert(r.find_by_name_pos("max") == -1);
	assert(r.find_by_name_pos("Max") == 0);
	assert(r.find_by_name_pos("Rex") == 1);

	assert(r.get_size_repo() == 2);
	assert(r.find_by_name("Max") == d);
	assert(r.find_by_name("aa") == Dog{});

	assert(r.remove_dog("Max") == 1);
	assert(r.get_size_repo() == 1);
	assert(r.remove_dog("Max") == -1);
	assert(r.get_size_repo() == 1);

	assert(r.update_dog(Dog{ "nu","Rex",9,"alt link" }) == 1);
	assert(r.get_elem_on_pos(0).getBreed() == "nu");
	

}

void test_controller()
{
	Repo r{};
	Controller c{ r };

	//test add
	assert(c.get_repo().get_size_repo() == 0);
	c.add_dog_controller("labrador", "Max", 5, "google.com");
	assert(c.get_repo().get_size_repo() == 1);
	assert(c.add_dog_controller("aa", "Max", 6, "link") == -1);
	//test remove
	assert(c.remove_dog_controller("Max") == 1);
	assert(c.remove_dog_controller("Max") == -1);
	//test update
	c.add_dog_controller("labrador", "Max", 5, "google.com");
	assert(c.update_dog_controller("aa", "Max", 3, "lala") == 1);
	assert(c.update_dog_controller("aa", "Rex", 3, "lala") == -1);
	//test add dog by breed to adoption list
	c.add_dogs_to_adoption_list_by_breed("", 30);
	assert(c.get_adoption_list().is_empty() == 0);
	//test adopt dog
	Dog d{ "aa","Max",3,"lala" };
	c.adopt_dog(d);
	assert(c.get_adoption_list().get_all_dogs().size() == 0);
	assert(c.get_adoption_list().get_user_dogs().size() == 1);
	//test clear list

	c.start_adoption_list();
	c.next_adoption_list();
	Dog d2 = c.get_adoption_list().get_current_dog();
}

void test_controller_2()
{

	Repo r{};
	Controller c{ r };
	c.add_dog_controller("labrador", "Max", 5, "google.com");
	c.add_dog_controller("bichon", "Alex", 7, "google.com");
	c.add_dog_controller("labrador", "Rex", 6, "google.com");
	c.add_dog_controller("labrador", "Mary", 12, "google.com");
	c.add_dog_controller("labrador", "Lala", 8, "google.com");

	std::vector<Dog> foo = c.get_repo().get_all_dogs();
	std::vector<Dog> bar(foo.size());

	// copy only dogs with breed labrador with age less or equal to 8:
	auto it = std::copy_if(foo.begin(), foo.end(), bar.begin(), [](Dog d) {return d.getBreed() == "labrador" && d.getAge()<=8; });
	bar.resize(std::distance(bar.begin(), it));
	//=> bar contains max, rex, lala
	assert(bar[0].getName() == "Max");
	assert(bar[1].getName() == "Rex");
	assert(bar[2].getName() == "Lala");
	assert(bar.size() == 3);
}
*/

int main()
{
	//test_repo();
	//test_controller();
	//test_controller_2();
	
	{
		
			Repo r{"dogs.txt"};
			//initialize_repo(r);
			Controller c{ r };
			Ui u{ c };
			
			u.start();
		
	}
	
	_CrtDumpMemoryLeaks();
	system("pause");
	
	return 0;
}