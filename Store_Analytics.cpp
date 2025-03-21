#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<cstring>
#include<windows.h>
#include<cmath>
using namespace std;
struct Store;
struct Employee;
struct GeoCoordinates;
struct Products;
struct SalesData;
struct Cluster;
struct subCluster;
struct Centroid;
struct Report;
struct StoreAnalytics;
struct Forecast;

struct StoreAnalytics
{
    double totalSales=0;
    double totaloperationalcost=0;
    double profit=0;
};


struct GeoCoordinates
{
double gLat=0;
double gLong=0;
};


struct Employee
{
int eID=0;
char* eName;
double Salary=0;
};


struct Products
{
char* SKU;
char* pName;
double unitPrice=0;
};


struct Report
{
Store* topStores;
Store* bottomStores;
};




struct Centroid
{
double cLat=0;
double cLong=0;
double Profit=0;
};

struct subCluster
{
char* ID;
char* Name;
Store* storesList;
Centroid subCenter;
int size=0;
};

struct Cluster
{
char* cID;
char* Name;
subCluster* subClusterList;
Store* sID;
Centroid Center;
int subSize;
int size=0;
};


struct Forecast
{
    char* month;
    double predictedSales;
};


struct Store
{
    char* sName;
    int sID=0;
    GeoCoordinates Location;
    double sMonthlyCost=0;
    Employee Manager;
    int S_count=0;
    Employee* Staff;
    StoreAnalytics sA;
    Forecast sF;
    int CustomerCountMonthly[24];
    double MonthlyIncome[24];
    

};


struct Salesdata
{
    Store sID;
    int ID;
    int P_num=0;
    Products* Prod;
    string Date;
    string Time;
    double TotalSaleAmount=0;
};

void initializeStorename(Store S[100],int i)
{
    //Store Name
    S[i].sName=new char[13];  //name can be of max 12 characters
    strcpy(S[i].sName,"UrbanEase");
    string temp=to_string(i+1);
    strcat(S[i].sName,temp.c_str());
}

void initializeStoreID(Store S[100],int i)
{
     //Store ID
         //Recheck if store with same Id exists
        S[i].sID=i+100;
}

void initializeStoreLocation(Store S[100],int i)
{
    //Addition part ensures decimal values are included
        //Location
        S[i].Location.gLat=(rand()%180-90)+(rand()%101)/100.0;
        S[i].Location.gLong=(rand()%360-180)+(rand()%101)/100.0;
}

void initializeMonthlyCost(Store S[100],int i)
{
    //Monthly cost of store
    S[i].sMonthlyCost=(rand()%3500+1000)+(rand()%101)/100.0;
    S[i].sA.totaloperationalcost=S[i].sMonthlyCost*24;
}

void initializeManager(Store S[100],int i)
{
     //Manager
     S[i].Manager.eID=rand()%900+100;
     //Ensure whether a manager with same ID exists;
     for (int j = 0; j < 100; j++)
     {
      if(S[i].Manager.eID==S[j].Manager.eID  && i!=j)   
         {
             S[i].Manager.eID=rand()%900+100;
             j=-1;
         }
     }
     S[i].Manager.Salary=rand()%500001+100000;
     fstream File;
     File.open("names.txt",ios::in);
     if(File.is_open())
     {
         string line;
         int num=rand()%10000;
         for(int k=1;k<=num;k++){
         getline(File,line);        
         }
         File.close();
         S[i].Manager.eName=new char[line.length()+1];
         strcpy(S[i].Manager.eName,line.c_str());
     }
}

void initializeStaff(Store S[100],int i)
{
    //Staff initialize
    S[i].S_count=rand()%50+50;
    S[i].Staff = new Employee[S[i].S_count];
    for (int j = 0; j < S[i].S_count; j++)
    {
        fstream File;
        File.open("names.txt",ios::in);
        if(File.is_open())
        {
            string line;
            int num=rand()%10000;
            for(int k=1;k<=num;k++){
            getline(File,line);        
            }
            File.close();
            S[i].Staff[j].eName=new char[line.length()+1];
            strcpy(S[i].Staff[j].eName,line.c_str());
        }
       S[i].Staff[j].Salary=rand()%301+100; 
       S[i].Staff[j].eID = rand()%90000+10000; //generating ID
       Again:
       for( int k = 0 ; k < S[i].S_count; k++ )  //Checking for same ID in store
       {
        if (S[i].Staff[j].eID==S[i].Staff[k].eID  && j!=k)
            {
                S[i].Staff[j].eID = rand()%90000+10000;
                k=-1;
            }
       }
           for(int p=0;p<100;p++)  //Checking for same ID in ALL stores
           {
               for(int k=0;k<S[p].S_count;k++)
               {
                   if(i!=p)
                   {
                       if(S[i].Staff[j].eID==S[p].Staff[k].eID)
                       {
                           S[i].Staff[j].eID = rand()%90000+10000;
                           goto Again; //Check if new generated ID again in same store
                       }
                   }
               }
           }
    }
}

void initializeMonthlyCustomerCount(Store S[100],int i)
{
    //initializing 0 for increasing later
    for(int j=0;j<24;j++)
    {
        S[i].CustomerCountMonthly[j]=0;
        S[i].MonthlyIncome[j]=0;
    }
}

void initializeProducts(Products Prod[35])
{
    //fetching product info
    fstream File("Products.txt");
    if(File.is_open())
    {
        for(int i=0;i<35;i++)
        {
            string temp;
            Prod[i].SKU=new char[12];
            Prod[i].pName=new char[16];
            getline(File,temp,',');
            strcpy(Prod[i].SKU,temp.c_str());
            getline(File,temp,',');
            strcpy(Prod[i].pName,temp.c_str());
            getline(File,temp);
            Prod[i].unitPrice=stof(temp);
        }
        File.close();
    }
    else
    cout<<"error with loading product file";
}

void initializeSales(Store S[100],Products Prod[35],Salesdata Sales[20000])
{
    srand(time(0));
    for(int i=0;i<20000;i++)
    {
        int st=rand()%100;
        Sales[i].ID=S[st].sID;

        Sales[i].P_num=rand()%4+1;  //no of products sold in that one sale
        
        Sales[i].Prod=new Products[Sales[i].P_num];
        for(int j=0;j<Sales[i].P_num;j++)
        {
            int num=rand()%35; //which product no is sold
            Sales[i].Prod[j].unitPrice=Prod[num].unitPrice;
            Sales[i].Prod[j].pName=new char[strlen(Prod[num].pName)+1];
            strcpy(Sales[i].Prod[j].pName,Prod[num].pName);
            Sales[i].Prod[j].SKU=new char[strlen(Prod[num].SKU)+1];
            strcpy(Sales[i].Prod[j].SKU,Prod[num].SKU);
            Sales[i].TotalSaleAmount+=Prod[num].unitPrice;
        }
        //Randomly initializing date
        int day, month, year;

        while (true)
        {
            year=rand()%3+23;
            month=rand()%12+1;
        
            if (year==23 && month<3)
            continue;

            if (year==25 && month>2) 
            continue;
        
            int maxDays;
            if(month == 2) 
                maxDays=(year==24)?29:28; // Leap year check for 2024
            else if(month == 4||month==6||month==9||month==11) //Months with 30 days
                maxDays = 30;
            else
                maxDays = 31;
            day=rand()%maxDays+1;
            break;
        }
        Sales[i].Date=(day<10?"0":"")+to_string(day)+"-";
        Sales[i].Date+=(month<10?"0":"")+to_string(month)+"-";
        Sales[i].Date+=to_string(year);

        //Randomly initializing time
        int temp=rand()%24;
        if(temp<10)
            Sales[i].Time="0"+to_string(temp);
        else
           Sales[i].Time=to_string(temp);
        Sales[i].Time+=":";
        temp=rand()%60;
        if(temp<10)
            Sales[i].Time+="0"+to_string(temp);
        else
            Sales[i].Time+=to_string(temp);
        Sales[i].Time+=":";
        temp=rand()%60;
        if(temp<10)
            Sales[i].Time+="0"+to_string(temp);
        else
            Sales[i].Time+=to_string(temp);

        //Changing values of stores according to sales
        int Month = stoi(Sales[i].Date.substr(3, 2));
        int Year = stoi(Sales[i].Date.substr(6, 2)); 

    if(Year==23) 
    {
        S[st].CustomerCountMonthly[Month-3]++;
        S[st].MonthlyIncome[Month-3]+=Sales[i].TotalSaleAmount;
    } 
    else if(Year==24) 
    { 
        S[st].CustomerCountMonthly[Month+9]++;
        S[st].MonthlyIncome[Month+9]+=Sales[i].TotalSaleAmount;
    } 
    else if(Year==25) 
    { 
        S[st].CustomerCountMonthly[Month+21]++;
        S[st].MonthlyIncome[Month+21]+=Sales[i].TotalSaleAmount;
    } 

        
    }

}

void CalculateAnalytics(Store S[100],Products Prod[35],Salesdata* Sales,int i)
{
    //calculate  analytics according to sales of a store
    for(int j=0;j<20000;j++)
    {
        if(Sales[j].ID==S[i].sID)
        {
            S[i].sA.totalSales=S[i].sA.totalSales + Sales[j].TotalSaleAmount;
        }
    }
    S[i].sA.profit=S[i].sA.totalSales-S[i].sA.totaloperationalcost;
}




void initializeData(Store S[100],Products Prod[35])
{
//initializing data
    initializeProducts(Prod);
    
    
    srand(time(0));
    for(int i=0;i<100;i++)
    {  
        initializeStorename(S,i);
        initializeStoreID(S,i);
        initializeStoreLocation(S,i);
        initializeMonthlyCost(S,i);
        initializeManager(S,i);
        initializeStaff(S,i);
        initializeMonthlyCustomerCount(S,i);
        
      
    }
}


//deleting all data 
void deleteData(Store S[100], Products Prod[35],Salesdata* Sales) {
    for (int i = 0; i < 100; i++) {
        delete[] S[i].sName;
        delete[] S[i].Manager.eName;
        delete[] S[i].sF.month;
        for (int j=0;j<S[i].S_count;j++) {
            delete[] S[i].Staff[j].eName;
        }
        delete[] S[i].Staff;
    }
    for (int i = 0; i < 35; i++) {
        delete[] Prod[i].SKU;
        delete[] Prod[i].pName;
    }


    for(int i=0;i<20000;i++)
    {
        for(int j=0;j<Sales[i].P_num;j++)
        {
            delete[] Sales[i].Prod[j].pName;
            delete[] Sales[i].Prod[j].SKU;
        } 
        delete[] Sales[i].Prod; 
    }
    delete[] Sales;
}

//Saving stores data in file
void SaveData(Store S[100])
{
    ofstream File("StoreData.txt");
    if(File.is_open())
    {
        for (int i = 0; i < 100; i++)
        {
            File<<S[i].sName<<',';
            File<<S[i].sID<<',';
            File<<S[i].Location.gLat<<',';
            File<<S[i].Location.gLong<<',';
            File<<S[i].sMonthlyCost<<',';
            File<<S[i].Manager.eID<<',';
            File<<S[i].Manager.eName<<',';
            File<<S[i].Manager.Salary<<',';
            File<<S[i].S_count<<',';
            for(int j=0;j<S[i].S_count;j++)
            {
                File<<S[i].Staff[j].eID<<',';
                File<<S[i].Staff[j].eName<<',';
                File<<S[i].Staff[j].Salary<<',';
            }
            File<<S[i].sA.profit<<',';
            File<<S[i].sA.totaloperationalcost<<',';
            File<<S[i].sA.totalSales<<',';
            for(int j=0;j<24;j++)
            {
                File<<S[i].CustomerCountMonthly[j]<<',';
            }
            for(int j=0;j<24;j++)
            {
                File<<S[i].MonthlyIncome[j]<<',';
            }

        }
        File.close();    
    }
}

//Saving Sales data in file
void SaveSales(Salesdata* Sales)
{
ofstream File("SalesData.txt");
if(File.is_open())
{
    for(int i=0;i<20000;i++)
    {
        File<<Sales[i].ID<<',';
        File<<Sales[i].P_num<<',';
        for(int j=0;j<Sales[i].P_num;j++)
        {
            File<<Sales[i].Prod[j].SKU<<',';
            File<<Sales[i].Prod[j].pName<<',';
            File<<Sales[i].Prod[j].unitPrice<<',';
        }
        File<<Sales[i].Date<<',';
        File<<Sales[i].Time<<',';
        File<<Sales[i].TotalSaleAmount<<',';
    }
}
    File.close();
}


//fetching store data
void LoadData(Store S[100])
{
    ifstream File("StoreData.txt");
    if(File.is_open())
    {
        string line;
            for(int i=0;i<100;i++)
            {
            getline(File,line,',');
            S[i].sName=new char[line.length()+1];
            strcpy(S[i].sName,line.c_str());
            getline(File,line,',');
            S[i].sID=stoi(line);
            getline(File,line,',');
            S[i].Location.gLat=stof(line);
            getline(File,line,',');
            S[i].Location.gLong=stof(line);
            getline(File,line,',');
            S[i].sMonthlyCost=stof(line);
            getline(File,line,',');
            S[i].Manager.eID=stoi(line);
            getline(File,line,',');
            S[i].Manager.eName=new char [line.length()+1];
            strcpy(S[i].Manager.eName,line.c_str());
            getline(File,line,',');
            S[i].Manager.Salary=stof(line);
            getline(File,line,',');
            S[i].S_count=stoi(line);
            S[i].Staff=new Employee[S[i].S_count];
            for(int j=0;j<S[i].S_count;j++)
            {
                getline(File,line,',');
                S[i].Staff[j].eID=stoi(line);
                getline(File,line,',');
                S[i].Staff[j].eName=new char[line.length()+1];
                strcpy(S[i].Staff[j].eName,line.c_str());
                getline(File,line,',');
                S[i].Staff[j].Salary=stof(line);
            }
            getline(File,line,',');
            S[i].sA.profit=stof(line);
            getline(File,line,',');
            S[i].sA.totaloperationalcost=stof(line);
            getline(File,line,',');
            S[i].sA.totalSales=stof(line);
            for(int j=0;j<24;j++)
            {
             getline(File,line,',');
             S[i].CustomerCountMonthly[j]=stoi(line);   
            }
            for(int j=0;j<24;j++)
            {
             getline(File,line,',');
             S[i].MonthlyIncome[j]=stof(line);   
            }
            }
            File.close();
    }
}
//fetching product info
void LoadProducts(Products Prod[35])
{
    ifstream File("Products.txt");
    if(File.is_open())
    {
        for(int i=0;i<35;i++)
        {
            string temp;
            Prod[i].SKU=new char[12];
            Prod[i].pName=new char[16];
            getline(File,temp,',');
            strcpy(Prod[i].SKU,temp.c_str());
            getline(File,temp,',');
            strcpy(Prod[i].pName,temp.c_str());
            getline(File,temp);
            Prod[i].unitPrice=stof(temp);
        }
        File.close();
    }
    else
    cout<<"error with loading product file";
}
//fetching sales data
void LoadSales(Salesdata* Sales)
{
    ifstream File("SalesData.txt");
    if(File.is_open())
    {
        for(int i=0;i<20000;i++)
        {
        string line;
        getline(File,line,',');
        Sales[i].ID=stoi(line);
        getline(File,line,',');
        Sales[i].P_num=stoi(line);
        Sales[i].Prod=new Products[Sales[i].P_num];
        for(int j=0;j < Sales[i].P_num;j++)
        {
            getline(File,line,',');
            Sales[i].Prod[j].SKU=new char[line.length()+1];
            strcpy(Sales[i].Prod[j].SKU,line.c_str());
            getline(File,line,',');
            Sales[i].Prod[j].pName=new char[line.length()+1];
            strcpy(Sales[i].Prod[j].pName,line.c_str());
            getline(File,line,',');
            Sales[i].Prod[j].unitPrice=stof(line);
        } 
        getline(File,line,',');
        Sales[i].Date=line;
        getline(File,line,',');
        Sales[i].Time=line;
        getline(File,line,',');
        Sales[i].TotalSaleAmount=stof(line);
        }
    }
}

void Store_Deep(Store &TO,const Store &BY)
{
    TO.sID=BY.sID;
    TO.Location=BY.Location;
    TO.sMonthlyCost=BY.sMonthlyCost;
    TO.sA=BY.sA;
    TO.sF=BY.sF;
    TO.S_count=BY.S_count;

    for (int i=0;i<24;i++) {
        TO.CustomerCountMonthly[i]=BY.CustomerCountMonthly[i];
        TO.MonthlyIncome[i]=BY.MonthlyIncome[i];
    }
    TO.sName=new char[strlen(BY.sName)+1];
    strcpy(TO.sName,BY.sName);

    TO.Manager.eName=new char[strlen(BY.Manager.eName)+1];
    strcpy(TO.Manager.eName,BY.Manager.eName);
    TO.Manager.eID=BY.Manager.eID;
    TO.Manager.Salary=BY.Manager.Salary;

    TO.Staff=new Employee[BY.S_count];  
        for(int i=0;i<BY.S_count;i++) 
        {
            TO.Staff[i].eID=BY.Staff[i].eID;
            TO.Staff[i].Salary=BY.Staff[i].Salary;
            TO.Staff[i].eName=new char[strlen(BY.Staff[i].eName) + 1];
            strcpy(TO.Staff[i].eName, BY.Staff[i].eName);
        }
}

void SortOverall(Store S[100],Products P[35],Salesdata* Sales)
{
    Report R1;
    R1.topStores=new Store[10];
    R1.bottomStores=new Store[5];
    int top[10]={0};
    int bottom[5]={0};
    double score[100]={0};
    double temp[100]={0};
    double growthRate[100]={0};
    for(int i=0;i<100;i++)
    {   
        for(int j=1;j<24;j++)
        {
            growthRate[i]=growthRate[i]+(S[i].MonthlyIncome[j]-S[i].MonthlyIncome[j-1]);
        }
        growthRate[i]/=23.0;
    }
    for(int i=0;i<100;i++)
    {
        score[i]=(S[i].sA.profit*0.5)+(growthRate[i]*0.3)+(S[i].sA.totalSales)*0.2;
        temp[i]=score[i];
    }

    for(int i=0;i<5;i++)
    {
        int min=INT_MAX;
        for(int j=0;j<100;j++)
        {
            if(min>score[j] && score[j]!=INT_MIN)
            {
                min=score[j];
                bottom[i]=j;
            }
        }
        score[bottom[i]]=INT_MIN;
    }
    for(int i=0;i<10;i++)
    {
        int max=INT_MIN;
        for(int j=0;j<100;j++)
        {
            if(max<score[j] && score[j]!=INT_MAX)
            {
                max=score[j];
                top[i]=j;
            }
        }
        score[top[i]]=INT_MAX;
    }
    for(int i=0;i<10;i++)
    {
        Store_Deep(R1.topStores[i],S[top[i]]);
    }
    for(int i=0;i<5;i++)
    {
        Store_Deep(R1.bottomStores[i],S[bottom[i]]);
    }
    cout<<"The top 10 stores are : "<<endl;
    cout<<"     Store ID     Store Name          Performance Score"<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<setw(3)<<left<<i+1<<"  ";
        cout<<R1.topStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.topStores[i].sName;
        cout<<temp[top[i]]<<endl;
    }
    cout<<"The bottom 5 stores are : "<<endl;
    cout<<"     Store ID     Store Name          Performance Score"<<endl;
    for(int i=4;i>=0;i--)
    {
        cout<<setw(3)<<left<<100-i<<"  ";
        cout<<R1.bottomStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.bottomStores[i].sName;
        cout<<temp[bottom[i]]<<endl;
    }   
    for (int i=0;i<10;i++) 
        delete[] R1.topStores[i].sName;
    for (int i=0;i<5;i++) 
        delete[] R1.bottomStores[i].sName;

    delete[] R1.bottomStores;
    delete[] R1.topStores;
}

void SortByProfit(Store S[100],Products P[35],Salesdata* Sales)
{

    Report R1;
    R1.topStores=new Store[10];
    R1.bottomStores=new Store[5];
    int top[10];  //array to store index of top 10 values
    int bottom[5]; //array to store index of bottom 5 values
    double score[100];  //array to store score of all 100 stores
    for(int i=0;i<100;i++)
    {
        score[i]=S[i].sA.profit;
    }
    for(int i=0;i<5;i++)
    {
        int min=INT_MAX;
        for(int j=0;j<100;j++)
        {
            if(min>score[j] && score[j]!=INT_MIN)
            {
                min=score[j];
                bottom[i]=j;
            }
        }
        score[bottom[i]]=INT_MIN;
    }
    for(int i=0;i<10;i++)
    {
        int max=INT_MIN;
        for(int j=0;j<100;j++)
        {
            if(max<score[j] && score[j]!=INT_MAX)
            {
                max=score[j];
                top[i]=j;
            }
        }
        score[top[i]]=INT_MAX;
    }
    for(int i=0;i<10;i++)
    {
        Store_Deep(R1.topStores[i],S[top[i]]);//copying store in report array
    }
    for(int i=0;i<5;i++)
    {
        Store_Deep(R1.bottomStores[i],S[bottom[i]]);//copying store in report array
    }
    cout<<"The top 10 stores are : "<<endl;
    cout<<"     Store ID     Store Name          Profit"<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<setw(3)<<left<<i+1<<"  ";
        cout<<R1.topStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.topStores[i].sName;
        cout<<S[top[i]].sA.profit<<'$'<<endl;
    }
    cout<<"The bottom 5 stores are : "<<endl;
    cout<<"     Store ID     Store Name          Profit"<<endl;
    for(int i=4;i>=0;i--)
    {
        cout<<setw(3)<<left<<100-i<<"  ";
        cout<<R1.bottomStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.bottomStores[i].sName;
        cout<<S[bottom[i]].sA.profit<<'$'<<endl;
    }   
    for (int i=0;i<10;i++) 
        delete[] R1.topStores[i].sName;
    for (int i=0;i<5;i++) 
        delete[] R1.bottomStores[i].sName;
    delete[] R1.bottomStores;
    delete[] R1.topStores;
    
}

void SortBySales(Store S[100],Products P[35],Salesdata* Sales)
{
    Report R1;
    R1.topStores=new Store[10];
    R1.bottomStores=new Store[5];
    int top[10];
    int bottom[5];
    double score[100];
    double temp[100]={0};
    for(int i=0;i<100;i++)
    {
        score[i]=temp[i]=0;
        for(int j=0;j<24;j++)
        score[i]=score[i]+S[i].CustomerCountMonthly[j];
        temp[i]=score[i];
    }

    for(int i=0;i<5;i++)
    {
        int min=INT_MAX;
        for(int j=0;j<100;j++)
        {
            if(min>score[j] && score[j]!=INT_MIN)
            {
                min=score[j];
                bottom[i]=j;
            }
        }
        score[bottom[i]]=INT_MIN;
    }
    for(int i=0;i<10;i++)
    {
        int max=INT_MIN;
        for(int j=0;j<100;j++)
        {
            if(max<score[j] && score[j]!=INT_MAX)
            {
                max=score[j];
                top[i]=j;
            }
        }
        score[top[i]]=INT_MAX;
    }
    for(int i=0;i<10;i++)
    {
        Store_Deep(R1.topStores[i],S[top[i]]);
    }
    for(int i=0;i<5;i++)
    {
        Store_Deep(R1.bottomStores[i],S[bottom[i]]);
    }
    cout<<"The top 10 stores are : "<<endl;
    cout<<"     Store ID     Store Name          No. Of Sales"<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<setw(3)<<left<<i+1<<"  ";
        cout<<R1.topStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.topStores[i].sName;
        cout<<temp[top[i]]<<endl;
    }
    cout<<"The bottom 5 stores are : "<<endl;
    cout<<"     Store ID     Store Name          No. Of Sales"<<endl;
    for(int i=4;i>=0;i--)
    {
        cout<<setw(3)<<left<<100-i<<"  ";
        cout<<R1.bottomStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.bottomStores[i].sName;
        cout<<temp[bottom[i]]<<endl;
    }   
    for (int i=0;i<10;i++) 
        delete[] R1.topStores[i].sName;
    for (int i=0;i<5;i++) 
        delete[] R1.bottomStores[i].sName;

    delete[] R1.bottomStores;
    delete[] R1.topStores;



}

void SortByGrowth(Store S[100],Products P[35],Salesdata* Sales)
{
    Report R1;
    R1.topStores=new Store[10];
    R1.bottomStores=new Store[5];
    int top[10];
    int bottom[5];
    double score[100];
    double temp[100]={0};
    for(int i = 0; i < 100; i++) {
        score[i] = 0; 
        for(int j=1;j<24;j++)
        {
            if(S[i].MonthlyIncome[j-1]!=0)
            score[i]+=((S[i].MonthlyIncome[j]-S[i].MonthlyIncome[j-1])/S[i].MonthlyIncome[j-1])*100;
        }
        score[i] /= 23.0;
        temp[i]=score[i];
    }

    for(int i=0;i<5;i++)
    {
        int min=INT_MAX;
        for(int j=0;j<100;j++)
        {
            if(min>score[j] && score[j]!=INT_MIN)
            {
                min=score[j];
                bottom[i]=j;
            }
        }
        score[bottom[i]]=INT_MIN;
    }
    for(int i=0;i<10;i++)
    {
        int max=INT_MIN;
        for(int j=0;j<100;j++)
        {
            if(max<score[j] && score[j]!=INT_MAX)
            {
                max=score[j];
                top[i]=j;
            }
        }
        score[top[i]]=INT_MAX;
    }
    for(int i=0;i<10;i++)
    {
        Store_Deep(R1.topStores[i],S[top[i]]);
    }
    for(int i=0;i<5;i++)
    {
        Store_Deep(R1.bottomStores[i],S[bottom[i]]);
    }
    cout<<"The top 10 stores are : "<<endl;
    cout<<"     Store ID     Store Name          Growth Percentage"<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<setw(3)<<left<<i+1<<"  ";
        cout<<R1.topStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.topStores[i].sName;
        cout<<temp[top[i]]<<'%'<<endl;
    }
    cout<<"The bottom 5 stores are : "<<endl;
    cout<<"     Store ID     Store Name          Growth Percentage"<<endl;
    for(int i=4;i>=0;i--)
    {
        cout<<setw(3)<<left<<100-i<<"  ";
        cout<<R1.bottomStores[i].sID<<"          ";
        cout<<setw(20)<<left<<R1.bottomStores[i].sName;
        cout<<temp[bottom[i]]<<'%'<<endl;
    }   
    for (int i=0;i<10;i++) 
        delete[] R1.topStores[i].sName;
    for (int i=0;i<5;i++) 
        delete[] R1.bottomStores[i].sName;

    delete[] R1.bottomStores;
    delete[] R1.topStores;


}

void Predict_Sales(Store &S)
{

    //am taking two windows of 6 and 12 months and make predictions from both after that i will find between both the predictions and then 
    //find the confidence level using that gap between the both predictions

    //My actual prediction is the one with 6 month window

    //In finding prediction we also take account of the avg growth rate of last 6 months 
    strcpy(S.sF.month,"March 2025");
    double avgG[2]={0};
    double deviation=0;
    double growth=0;
    double C_Gap=0;
    

    //We are taking a window of 6 months
    for(int i=23;i>17;i--)
    {
        avgG[0]=avgG[0]+S.MonthlyIncome[i];
    }
    avgG[0]/=6;

    for(int i=17;i<23;i++)
    {
        growth+=(S.MonthlyIncome[i+1]-S.MonthlyIncome[i])/S.MonthlyIncome[i];
    }
    growth/=5;

    //finding  standard deviation in last 6 month sales
    for(int i=0;i<6;i++)
    deviation+=pow(S.MonthlyIncome[23-i]-avgG[0],2);
    deviation=sqrt(deviation/6.0);
    
    
    for(int i=0;i<12;i++)
    {
        avgG[1]=avgG[1]+S.MonthlyIncome[23-i];
    }
    avgG[1]/=12;
    S.sF.predictedSales=avgG[0]*(1+growth);
    if(avgG[1]!=0)
    //finding gap between 6 and 12 month prediction
    C_Gap=((abs(avgG[0]-avgG[1])/avgG[1])*100) + (deviation/avgG[0])*20;
    double C_level=100-(C_Gap*1.5);
    if(C_level<5)  //minimum threshold
    C_level=5;
    cout<<"The predicted Sales for "<<S.sF.month<<" are : "<<S.sF.predictedSales<<'$'<<endl;
    cout<<"\nThe Confidence level is : "<<setprecision(2)<<fixed<<C_level<<'%'<<endl;
    
    //prediction if sale is decreased from last month
    if(S.sF.predictedSales<S.MonthlyIncome[23])
    cout<<"On Warning!!"<<endl<<endl<<endl;

}

void initializeForecast(Store S[100])
{
	for(int i=0;i<100;i++)
	{
		S[i].sF.month=new char[15];
	}
}

void initializeSubCluster(Cluster &C,int size)
{
    //initializing subCluster struct
    for(int i=0;i<size;i++)
    {
        string temp=string(C.cID)+"S"+to_string(i+1);
        C.subClusterList[i].ID=new char[temp.length()+1]; 
        strcpy(C.subClusterList[i].ID,temp.c_str());
        temp="Sub "+ to_string(i+1);
        C.subClusterList[i].Name=new char[temp.length()+1];
        strcpy(C.subClusterList[i].Name,temp.c_str());
        C.subClusterList[i].storesList=new Store[100];
        C.subClusterList[i].subCenter.Profit=C.sID[i].sA.profit;
    } 
}


void initializeCluster(Cluster* C,Store S[100],int size)
{
    //initializing cluster struct
    for(int i=0;i<size;i++)
    {
        string temp="C"+to_string(i+1);
        C[i].cID=new char[temp.length()+1];
        strcpy(C[i].cID,temp.c_str());

        temp="Cluster "+to_string(i+1);
        C[i].Name=new char[temp.length()+1];
        strcpy(C[i].Name,temp.c_str());
        C[i].sID=new Store[100];
        C[i].subSize=3;
        C[i].subClusterList=new subCluster[C[i].subSize];
        initializeSubCluster(C[i],C[i].subSize);     

        C[i].Center.cLat=S[i].Location.gLat;
        C[i].Center.cLong=S[i].Location.gLong;
    }
}

void UpdateCentroidSub(Cluster &C,int num,int i)
{
    //initializing centroid of sub cluster
C.subClusterList[num].subCenter.Profit=(C.subClusterList[num].subCenter.Profit+C.sID[i].sA.profit)/2;
}

void SubClustering(Cluster &C, Store S[100], int subSize,int size)
{
    double d[subSize];
    for(int i=0;i<C.size;i++)
    {
        for(int j=0;j<C.subSize;j++)
        {
            d[j]=sqrt(pow(C.sID[i].sA.profit-C.subClusterList[j].subCenter.Profit,2));  //euclidean distance 
        }
        int index=0;
            double small=INT_MAX;
        for(int j=0;j<size;j++)
        {
            if(small>d[j])   //finding smallest answer of euclidean distance from centroids of all sub clusters to store
            {
                small=d[j];
                index=j;
            }
        }
        Store_Deep(C.subClusterList[index].storesList[C.subClusterList[index].size],C.sID[i]);  //adding store to subcluster
        C.subClusterList[index].size++;  
        UpdateCentroidSub(C,index,i);  //updating centroid
    }
}

void UpdateCentroid(Cluster &C)
{
    //update centroid of cluster
C.Center.cLat=(C.Center.cLat+C.sID[C.size-1].Location.gLat)/2.0;
C.Center.cLong=(C.Center.cLong+C.sID[C.size-1].Location.gLong)/2.0;
}

void Clustering (Store S[100],Cluster C[3],int size)
{
    double d[size];
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<size;j++)
        {
            d[j]=sqrt(pow(S[i].Location.gLat-C[j].Center.cLat,2)+pow(S[i].Location.gLong-C[j].Center.cLong,2));//euclidean distance
        }
            int index=0;
            double small=INT_MAX;
        for(int j=0;j<size;j++)
        {
            if(small>d[j])  //finding smallest distance
            {
                small=d[j];
                index=j;
            }
        }
            Store_Deep(C[index].sID[C[index].size],S[i]);  //adding store with nearest cluster
            C[index].size++;
            UpdateCentroid(C[index]);  //updating centroid
    }
    for(int i=0;i<size;i++)
    { 
        //making subcluster for each cluster
        SubClustering(C[i],S,C[i].subSize,size);
    }
}
  //deleting cluster and subcluster
  void deleteClusters(Cluster C[3],int num) {
    for (int i = 0; i < num; i++) {
        delete[] C[i].cID;
        delete[] C[i].Name;
        for (int j=0;j<C[i].subSize;j++) {
            delete[] C[i].subClusterList[j].ID;
            delete[] C[i].subClusterList[j].Name;
            for (int k = 0; k < C[i].subClusterList[j].size; k++) 
            {
                delete[] C[i].subClusterList[j].storesList[k].sName;
                delete[] C[i].subClusterList[j].storesList[k].Manager.eName;
                //delete staff
                for (int m = 0; m < C[i].subClusterList[j].storesList[k].S_count; m++) {
                    delete[] C[i].subClusterList[j].storesList[k].Staff[m].eName;
                }
                delete[] C[i].subClusterList[j].storesList[k].Staff;
            }
            delete[] C[i].subClusterList[j].storesList;
        }
        delete[] C[i].subClusterList;
        for (int j = 0; j < C[i].size; j++) {
            delete[] C[i].sID[j].sName;
            delete[] C[i].sID[j].Manager.eName;
            for (int k = 0; k < C[i].sID[j].S_count; k++) {
                delete[] C[i].sID[j].Staff[k].eName;

            }
            delete[] C[i].sID[j].Staff;
        }
        delete[] C[i].sID;
    }
}



void printClusterInfo(Cluster* C)
{
    for(int i=0;i<3;i++)
    {
        cout<<endl<<endl<<"Cluster "<<i+1;
        for(int k=0;k<3;k++)
    {
            cout<<endl<<endl<<"Subcluster "<<k+1<<endl<<endl;
            cout<<"Store ID      Store Name"<<endl;
        for(int j=0;j<C[i].subClusterList[k].size;j++)
        {
        cout<<C[i].subClusterList[k].storesList[j].sID<<"           "<<C[i].subClusterList[k].storesList[j].sName<<endl;        
        }
    }
        cout<<endl<<endl<<endl;
    }
}

void GraphMonthlySales(Store S[100])
{
    cout<<"One * is equal to 150 $\n"<<endl;
    for (int i=0;i<100;i++)
    {
        double avg=0;
        for(int j=0;j<24;j++)
        avg=avg+S[i].MonthlyIncome[j];
        avg/=24;
        int criteria;
        criteria=avg/150;
        cout<<setw(12)<<left<<S[i].sName<<" : ";
        for(int j=0;j<criteria;j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
}


void GraphByProfit(Store S[100])
{
    cout<<"One * is equal to 1000$"<<endl<<endl;
    for(int i=0;i<100;i++)
    {
        int criteria;
        criteria=S[i].sA.profit/1000;
        cout<<setw(12)<<left<<S[i].sName<<" : ";
        if(criteria<0)
        {
            cout<<" In Loss "<<endl;
            continue;
        }
        
        for(int j=0;j<criteria;j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
}

void GraphByCluster(Cluster C[3])
{
    cout<<"One * is equal to 100,000$"<<endl;
    int highest=0;
    double highprofit=0;
    for(int i=0;i<3;i++)
    {
        cout<<setw(10)<<left<<C[i].Name<<" : ";
        double temp=0;
        for(int j=0;j<C[i].size;j++)
        {
            temp+=C[i].sID[j].sA.profit;
        }
        if(temp>highprofit)
        {
            highest=i;
            highprofit=temp;
        }
        int criteria=temp/100000;
        for(int j=0;j<criteria;j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
    cout<<C[highest].Name<<"  with ID  "<<C[highest].cID<<" is contributing most to the revenue !"<<endl;
}

void GraphByMonthlyTrend(Store S)
{
    string months[12] = {"March", "April", "May", "June","July", "August", "September", "October", "November", "December","January","February"};
    
    cout<<"One * represents 100$"<<endl;
    for(int i=0;i<12;i++)
    {
        int criteria;
        criteria=S.MonthlyIncome[i+12]/100;
        cout<<setw(10)<<left<<months[i]<<" : ";
        for(int j=0;j<criteria;j++)
        {
            cout<<"*";
        }
        cout<<endl;

    }
}

void GraphBySubCluster(Cluster C[3])
{
    cout<<"\nOne * is equal to 40,000$"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<"================"<<C[i].Name<<"================ "<<endl;
        for(int j=0;j< C[i].subSize;j++)
        {
        	int criteria=10;
            cout<<C[i].subClusterList[j].Name<<" : ";
            int revenue=0;
            for(int k=0;k<C[i].subClusterList[j].size;k++)
            {
                revenue+=C[i].subClusterList[j].storesList[k].sA.profit;
            }
            if (revenue<0)
            {
            	cout<<"Total Profit of subcluster is less than 0"<<endl;
            	continue;
			}
            if(revenue>1000000)
            criteria=revenue/100000;
            else if(revenue>500000)
            criteria=revenue/50000;
            else if(revenue>100000)
            criteria=revenue/10000;
            else
            criteria=revenue/5000;
            if(criteria==0)
            {
                cout<<"Sales less than 40,000"<<endl;
                continue;
            }
            for(int k=0;k<criteria;k++)
            cout<<"*";
            cout<<endl;
        }
    }
}

void Run()
{
    Store S[100];
    Products Prod[35];
    Cluster C[3];
    Salesdata* Sales = new Salesdata[20000];
    ifstream Check("StoreData.txt");
    ifstream Check2("SalesData.txt");
    if(Check && Check2)
    {
        Check.close();
        Check2.close();
        LoadData(S);
        LoadProducts(Prod);
        LoadSales(Sales);
    }
    else
    {
        Check.close();
        Check2.close();
        initializeData(S,Prod);
        initializeSales(S,Prod,Sales);
        for(int i=0;i<100;i++)
        CalculateAnalytics(S,Prod,Sales,i);
        SaveData(S);
        SaveSales(Sales);
    }
    initializeForecast(S);
    initializeCluster(C,S,3);
    Clustering(S,C,3);
   int choice=0;
   while(true)
   {
   cout<<"Performance Sorting : \nClick-1 to exit\n1.Overall Performance \n2.By Profit\n3.By Growth Rate\n";
   cout<<"4.Predict Sales\n5.Sort by no of Sales\n6.Print Cluster Info\n7.Graph by Average Monthly Sales\n8.Graph by Profits\n9.Graph by Monthly Sales Trend\n10.Graph By Profit of each cluster\n11.Graph by Profit of all SubClusters\nEnter your choice : ";
   cin>>choice;
   cout<<endl<<endl;
    if(choice==-1)
    {
        system("CLS");
        cout<<"Thanks for using the system!";
        exit(0);
    }   
    while(choice<1 || choice >11)
   {
    cout<<"\nInvalid\nEnter your choice again : ";
    cin>>choice;
    if(choice==-1)
    {
        system("CLS");
        cout<<"Thanks for using the system!";
        exit(0);
    } 
   }
   switch(choice)
   {
       case 1:
           SortOverall(S,Prod,Sales);
       break;
       case 2:
           SortByProfit(S,Prod,Sales);
       break;
       case 3:
           SortByGrowth(S,Prod,Sales);
       break;
       case 4:
           int temp_choice;
           cout<<"\nEnter Store you want to predict ";
           cin>>temp_choice;
           while(temp_choice<1 || temp_choice>100)
           {
               cout<<"\nInvalid\nEnter Store you want to predict ";
               cin>>temp_choice;   
           }
           Predict_Sales(S[temp_choice-1]);
        break;
        case 5:
            SortBySales(S,Prod,Sales);
        break;
        case 6:
            printClusterInfo(C);
        break;
        case 7:
           GraphMonthlySales(S);
        break;
        case 8:
           GraphByProfit(S);
        break;
        case 9:
        cout<<"\nEnter Store you want Monthly Sales Trend : ";
        cin>>temp_choice;
        while(temp_choice<1 || temp_choice>100)
        {
            cout<<"\nInvalid\nEnter Store you want to Monthly Sales Trend ";
            cin>>temp_choice;   
        }
            GraphByMonthlyTrend(S[temp_choice-1]);
            break;
        case 10:
           GraphByCluster(C);
        break;
        case 11:
            GraphBySubCluster(C);
        break;
   }
   }

    deleteData(S,Prod,Sales);
    deleteClusters(C,3);
    cout<<"a";

} 


int main()
{

    Run();
    return 0;
}