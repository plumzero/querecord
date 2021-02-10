#include <cstdio>
#include <string>

class Employee {
public:
	std::string first_name, family_name;
	short department;
public:
	void emp_print() { printf("In employ\n"); }
};

class Manager : public Employee {
public:
	short level;
public:
	void mgr_print() { printf("In Manager\n"); }
};

int main() {
	Manager mgr;
	
	mgr.first_name = "li";
	mgr.level = 100;	

	Employee emp_copy = mgr;
	printf("first_name = %s\n", emp_copy.first_name.c_str());
	//printf("level = %d\n", emp_copy.level);	// compile error: no this member
	emp_copy.emp_print();
	//emp_copy.mgr_print();				// compile error: no this member
	
	Employee* pemp = &mgr;
	printf("first_name = %s\n", pemp->first_name.c_str());
	//printf("level = %d\n", pemp->level);		// compile error: no this member
	pemp->emp_print();
	//pemp->mgr_print();				// compile error: no this member

	return 0;
}
