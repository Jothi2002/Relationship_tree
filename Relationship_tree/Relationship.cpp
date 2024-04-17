#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include<sstream>

class Person {
public:
    std::string name;
    std::string gender;
    Person* parent;
    std::vector<Person*> children;

    Person(const std::string &n, const std::string &g):name(n),gender(g), parent(nullptr) 
    {

    }
};

class familytree {
private:
    std::unordered_map<std::string, Person*> p;

public:
    void Relationship(const std::string &cname, const std::string &pname, const std::string &gender) {
        if (!p.count(cname)) {
            p[cname] = new Person(cname, gender); //cname-childname,pname-parentname
        }
        if (!p.count(pname)) {
            p[pname] = new Person(pname,"");
        }

        Person* child = p[cname];
        Person* parent = p[pname];
        child->parent = parent;
        parent->children.push_back(child);
    }

    Person* findperson(const std::string  &name) {
        if (p.count(name)) {
            return p[name];
        }
        return nullptr;
    }

    std::string find_grandfather(const std::string &pname) {
        Person* person = findperson(pname);
        if (!person || !person->parent || !person->parent->parent) {
            return "unknown";
        }
        return person->parent->parent->name;
    }

    std::vector<std::string> find_cousinsisters(const std::string &pname) {
        std::vector<std::string> cousin_sisters;
        Person* person = findperson(pname);
        if (!person || !person->parent || !person->parent->parent) {
            return cousin_sisters;
        }
std::string parent_gender = person->parent->gender;
        Person* grandparent = person->parent->parent;
        for (Person* auntuncle : grandparent->children) {
            if (auntuncle != person->parent && auntuncle->gender == parent_gender) {
                for (Person* cousin : auntuncle->children) {
                    if (cousin->gender == "female" && cousin != person->parent) {
                        cousin_sisters.push_back(cousin->name);
                    }
                }
            }
        }
        return cousin_sisters;
    }

    std::vector<std::string> find_cousinbrothers(const std::string& pname) {
        std::vector<std::string> cousin_brothers;
        Person* person = findperson(pname);
        if (!person || !person->parent || !person->parent->parent) {
            return cousin_brothers;
        }
std::string parent_gender = person->parent->gender;
        Person* grandparent = person->parent->parent;
        for (Person* auntuncle : grandparent->children) {
            if (auntuncle != person->parent && auntuncle->gender == parent_gender) {
                for (Person* cousin : auntuncle->children) {
                    if (cousin->gender == "male" && cousin != person->parent) {
                        cousin_brothers.push_back(cousin->name);
                    }
                }
            }
        }
        return cousin_brothers;
    }
    std::vector<std::string> find_cousin(const std::string& pname) {
    std::vector<std::string> cousin;
    Person* person = findperson(pname);
    if (!person || !person->parent || !person->parent->parent) {
        return cousin;
    }

    std::string parent_gender = person->parent->gender;

    Person* grandparent = person->parent->parent;
    for (Person* auntuncle : grandparent->children) {
        if (auntuncle != person->parent && auntuncle->gender != parent_gender) {
            for (Person* cousin_person : auntuncle->children) {
            cousin.push_back(cousin_person->name);
                }
            }
        }

    return cousin;
}

};

int main() {
    familytree family;
    std::string input;
    std::cout<<"Enter 'a' if you want to run sample data or Enter 'b' if you want to run your own data : ";
    std::cin>>input;
   
    if(input=="a")
    {
    family.Relationship("kavin", "mani","male");
    family.Relationship("manoj", "mani","male");
    family.Relationship("mathavan", "mani","male");
    family.Relationship("harini", "mani","female");
    family.Relationship("aravind","kavin", "male");
    family.Relationship("tharunya","manoj","female");
    family.Relationship("jose", "mathavan","female");
    family.Relationship("shan", "manoj","male");
    family.Relationship("karthi","harini","male");
    std::cout<<"relationship that i added"<<std::endl<<std::endl;
    std::cout<<"kavin is son of mani"<<std::endl;
std::cout<<"manoj is son of mani"<<std::endl;
std::cout<<"mathavan is son of mani"<<std::endl;
std::cout<<"harini is daughter of mani" <<std::endl;
std::cout<<"aravind is son of kavin"<<std::endl;
std::cout<<"tharunya is daughter of manoj"<<std::endl;
std::cout<<"jose is daughter of mathavan"<<std::endl;
std::cout<<"shan is son of manoj"<<std::endl;
std::cout<<"karthick is son of harini"<<std::endl<<std::endl<<std::endl;

    std::cout<< "family tree sample data"<<std::endl;
    std::cout<<"                     mani"<<std::endl;
    std::cout<<"    /            /          \\                   \\"<<std::endl;
    std::cout<<" kavin        manoj       mathavan             harini"<<std::endl;
    std::cout<<"    |         /   \\         |                    |" <<std::endl;
    std::cout<<"aravind    shan  tharunya   jose               karthi" <<std::endl<<std::endl ;    
 
    std::cout<<"output:"<<std::endl<<std::endl;
    std::cout << "grandfather:" << family.find_grandfather("aravind") << std::endl; // give person name here
    
    std::vector<std::string> cousin_sisters = family.find_cousinsisters("aravind");//give person name here
    // if (cousin_sisters.empty()) {
    //     std::cout << "No cousin brothers" << std::endl;}
       
        {
        std::cout << "cousin_sister :";
        for (const std::string& sister : cousin_sisters) {
        std::cout << sister<< "," ;
    }}
    std::cout << std::endl;

    std::vector<std::string> cousin_brothers = family.find_cousinbrothers("aravind");//give person name here
    // if (cousin_brothers.empty()) {
    //     std::cout << "No cousin brothers" << std::endl;}
       
        {
        std::cout << "cousin_brother :";
        for (const std::string& brother : cousin_brothers) {
        std::cout << brother << ",";
    }}
    std::cout << std::endl;
    std::vector<std::string> cousin = family.find_cousin("aravind");//give person name here
    std::cout << "cousin :";
    for (const std::string& cousin : cousin) {
        std::cout << cousin << ",";
    }
    std::cout << std::endl;

    }
    else if(input=="b"){
       std::cout << "Enter statements in the format 'childname,parentname,children_gender' ( eg. aravind,kavin,male). enter exit to finish\n";
        while (true) {
        std::cout << "Enter statement: ";
        std::getline(std::cin >> std::ws, input);
        if (input == "exit") {
            break;
        }

        std::istringstream iss(input);
        std::string childname, parentname, gender;
        std::getline(std::getline(iss >> std::ws, childname, ','), parentname, ',');
        std::getline(iss >> std::ws, gender);
   
        family.Relationship(childname, parentname, gender);
    }

// it allows user to ask queries
    std::cout<<"gf-grandfather,cs-cousin_sister,cb-cousin_brother";
    std::cout << "\nEnter queries  (eg. gf:person_name, cs:person_name, cb:person_name, c:person_name) enter exit to finish.\n";
    while (true) {
        std::cout << "Enter queries: ";
        std::getline(std::cin >> std::ws, input);
        if (input == "exit") {
            break;
        }

        std::istringstream iss(input);
        std::string relation, person;
        std::getline(iss >> std::ws, relation, ':');
        std::getline(iss >> std::ws, person);
std::string person_not_found = "Person not found in family tree.";
        if (relation == "gf") {
          std::string grand_father = family.find_grandfather(person);
        if (grand_father == "unknown") {
        if (!family.findperson(person)) {
            std::cout << person_not_found << std::endl;
        } else {
            std::cout << "no grandfather" << std::endl;
        }
    }
    std::cout << "grandfather: " << grand_father<<std::endl;
}

         else if (relation == "cs" || relation=="CS") {
            std::vector<std::string> cousin_sisters = family.find_cousinsisters(person);
            if(cousin_sisters.empty())
            {    if (!family.findperson(person)) {
            std::cout << person_not_found << std::endl;}
            else{
                std::cout<<"no cousin sisters"<<std::endl;
            }}
            else{
            std::cout << "cousin sisters: ";
            for (const std::string &sister : cousin_sisters) {
                std::cout << sister << ", ";
            }

            std::cout << std::endl;
            }}

         else if (relation == "cb"|| relation=="CB") {
            std::vector<std::string> cousin_brothers = family.find_cousinbrothers(person);
             if(cousin_brothers.empty())

            {
                   if (!family.findperson(person)) {
            std::cout << person_not_found << std::endl;}
            else{
                std::cout<<"no cousin brothers"<<std::endl;
            }}
            else{
            std::cout << "cousin brothers: ";
            for (const std::string &brother : cousin_brothers) {
                std::cout << brother << ", ";
            }
            std::cout << std::endl;
        } }
        else if (relation =="c" || relation=="C"){
            std::vector<std::string> cousin = family.find_cousin(person);
             if(cousin.empty()){
                    if (!family.findperson(person)) {
            std::cout << person_not_found << std::endl;}
                else{
                std::cout<<"no cousin"<<std::endl;
                }
            }
            else{
            std::cout << "Cousin : ";
            for (const std::string& cousin : cousin) {
                std::cout << cousin << ", ";
            }
            std::cout << std::endl;
        } }
        
    else{
        std::cout<<"invalid query:ask queries in the format 'gf'or 'cb' or 'cs' or 'c'"<<std::endl;
    }}}
    
    
    
    

    return 0;

}      
    
    
    