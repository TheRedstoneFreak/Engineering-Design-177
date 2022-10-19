#include<iostream>
#include<map>
#include<string>
using namespace std;
int main(){
   
   map<string, int> food;
   food["Apples"] = 30; //days
   food["Asparagus"] = 4;
   food["Avocadoes"] = 3;
   food["Beans"] = 5;
   food["Berries"] = 3;
   food["Broccoli"] = 6;
   food["Carrots"] = 80;
   food["Capsicum"] = 12;
   food["Cauliflower"] = 12;
   food["Celery"] = 25;
   food["Corn"] = 3;
   food["Citrus"] = 16;
   food["Cucumber"] = 11;
   food["Eggplant"] = 11;
   food["Lettuce"] = 11;
   food["Kiwi"] = 7;
   food["Mushrooms"] = 11;
   food["Onions"] = 80;
   food["Peaches"] = 3;
   food["Pears"] = 14;
   food["Peas"] = 6;
   food["Strawberries"] = 3;
   food["Tomatoes"] = 6;
   
    map <string,int> :: iterator iter;
   cout<<"keys"<<"  &  "<<"values"<<endl;
   for (iter = food.begin(); iter != food.end(); iter++)
   {
     cout << (*iter).first << "    " << (*iter).second << "\n";
   }
    return 0;
    }

    
