/**
 * File:Final Project
 * Developer: Dalles Marin
 * Email: dallasmarin80@icloud.com
 * Description: Program is a concordance generator for the first chapter of Alice in wonderland.
 */

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<ctype.h>
#include<sstream>
using namespace std;

//Declare class
class WordsStats
{
   //Declare all required variables
   protected:
       char file[20];
       string lines[1000];
       string word;
       string concord[1000];
       double line;
       int idx;
       int count[1000];
  
   //Declare all required constructors and methods
   public:
       WordsStats();
       void readFileName();
       int proessFileData();
       void printStats();
};

//Default constructor to initialize default values
WordsStats::WordsStats()
{
   line=0;
   idx=0;
}

//Method to read file name
void WordsStats::readFileName()
{
   cout << "Enter the text file name: " << std::endl;
   //read file name
   cin.get(file,100);
}      

//Method to read file and process data
int WordsStats::proessFileData()
{
   int i=0,j=0,k=0;
  
   ifstream ifs;
   //open text file
   ifs.open(file);
          
   if(!ifs.is_open())
   {
       cout<< "Unable to open file: " << std::endl;
       return 0;
   }
          
   string w;//temporary string
          
   //read all lines
   while(ifs.good())
   {
       getline(ifs,word);//read line by line
              
       //removing punctuations and converting upper case letters to lower case
       for(int i=0;i<word.length();i++)
       {
           if(!isalpha(word.at(i)))
           {
               if(word.at(i)!=' ')  
               for(int j=i;j<word.length()-1;j++)
               {
                   word.at(j)=word.at(j+1);
               }
               if(i==word.length()-1)
                   word.at(i)=' ';
               }
           }
          
           istringstream iss(word);
           while(iss>>w) //read each word in each line
           {
               bool flag=false;  
               int matchedAt=-1;
                  
               for(int k=0;k<idx;k++)
               {
                   if(concord[k]==w)
                   {
                       flag=true;
                       matchedAt=k;
                   }
               }
                  
               if(flag!=true)
               {
                   concord[idx] = w;
                   count[idx] = 1;
                  
                   stringstream num;
                   num<< line+1;
                   lines[idx] = num.str();
                   idx++;
               }
               else
               {
                   count[matchedAt]++;
                   stringstream numb;
                   numb<<line+1;
                   lines[matchedAt]=lines[matchedAt]+"," +numb.str();
               }
       }
       line=line+1;
   }          
return 1;
}//end of function      

//Method to print stats
void WordsStats::printStats()
{
   cout<<std::left<<std::setw(15)<<"Word"<<std::setw(3)<<" : " << "count" << std::setw(3) << " : " << "Occurences" << std::endl;
   std::cout<<"------------------------------------------------------------------------------------"<<std::endl;
          
   for(int l=0;l<idx;l++)
       cout<<left<<setw(15)<<concord[l]<<setw(5)<<" : "<<count[l]<<setw(3)<<" : "<<lines[l]<<endl;
}  

int main()
{
   //create instance of WordsStats
    WordsStats wordStats;
    wordStats.readFileName();
    wordStats.proessFileData();
    wordStats.printStats();

   return 0;
}
