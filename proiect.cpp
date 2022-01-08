#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<thread>
#include<unordered_map>
#include<chrono>
#include<math.h>
#include<stdlib.h>
#include <ctime>
using namespace std;
class RSA
{
    public:
    int p;
    int q;
    long int n, t, flag, e[100], d[100], temp[100], j, m[100],  i;
    vector< int> encryption( string x)
    {
        vector< int> en;
        p = 5;
        q = 7;
        if(are_distinct(p,q)==true)
        {
            n = p*q;
            t = (p - 1) * (q - 1);
            for (i = 0; x[i] != '\0'; i++)
                   { m[i] = x[i];}
            ce();
            long int pt, ct, key = e[0], k, len;
    i = 0;
    len = x.size();
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en.push_back(ct);
        i++;
    }
    en[i] = -1;
   return en;
        }
    }
    void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = check_prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}
    long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}
    int check_prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}
    int generate_prime()
    {
        while(true)
        {
            int r = rand();
            if(check_prime(r) == 1)
            {
                return r;
            }
        }
    }
    bool are_distinct( int x, int y)
    {
        if(x==y)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};
class Try_to_login:public RSA
{
    public:
    string Attempted_username;
    string attempted_pass;
    public:

    class struct_data
    {
    public:
    string Username;
    vector<int> password;
    };
    int login()
    {
        cout<<"Login"<<endl;
        cout<<"Input your username:"<<endl;
        cin>>Attempted_username;
        cout<<"Input your password:"<<endl;
        cin>>attempted_pass;
        vector<int> Encryption1 = encryption(attempted_pass);
        vector<struct_data> Vector = get_data("Operators.csv");
        vector< struct_data> Vector1 = get_data("Users.csv");
        bool flag = false;
        for( auto it = Vector.begin();it!=Vector.end();it++)
        {
            if(Encryption1 == it->password && Attempted_username == it->Username)
            {
                flag = true;
                cout<<"Succesfully logged in"<<endl;
                return 1;
            }
        }
        if(flag == false)
        {
        for(auto it = Vector1.begin();it!=Vector1.end();it++)
            {
                if(Encryption1 == it->password && Attempted_username == it->Username)
            {
                flag = true;
                cout<<"Succesfully logged in"<<endl;
                return 2;
            }
            }
        }
        if(flag==false)
        {
            bool flag1= false;
            for( auto it = Vector.begin();it!=Vector.end();it++)
            {
                if(it->Username == Attempted_username)
                {
                    flag1 = true;
                    throw 3;
                }
            }
            if(flag1==false)
            {
                for(auto it = Vector1.begin();it!=Vector1.end();it++)
                {
                    if(Attempted_username==it->Username)
                    {
                        flag1 =true;
                        throw 3;                        
                    }
                }
            }
            if(flag1==false)
            {
            throw 4;
            }
        }
    } 
   vector<struct_data> get_data(const char* input_file)
    {
        fstream file;
        file.open(input_file);
        vector<struct_data> data;
        if(file.is_open())
        {
            string line;
            while(getline(file, line))
            {
                struct_data s1;
                int c =0;
                for(auto i : line)
                {
                    c++;
                      if( i== ',')
                    {
                        break;
                    }
                    s1.Username.push_back(i);
                  
                }
                int b = 0;
                for(auto j = c;j<line.size();j++)//attention here
                {
                    if(isdigit(line[j]))
                    {
                        b = b*10 + line[j] - '0';
                    }
                    else
                    {
                        s1.password.push_back(b);
                        b=0;
                    }
                }
                s1.password.push_back(b);
                data.push_back(s1); 
            }
        }
        return data;
    }
};
class Try_Sign_in:public Try_to_login
{
    public:
    string Pass;
    string Email_Username;
    string verify_pass;
    class infos
{
    public:
    string data;
    string country;
};
    bool has_space_char(string x)
    {
        for(int i=0;i<x.length();i++)
        {
            if(x[i]==' ')
            {
                return true;
            }
        }
        return false;
    }
 vector<infos> get_info(const char* input_file)
   {
       ifstream file;
       file.open(input_file);
       string line;
       vector<infos> Data;
       while(getline(file,line))
        {
            int c=0;
            infos s1;
            for( auto it = line.begin();it!=line.end();it++)
            {
                c++;
                if((*it) == ',')
                {
                    break;
                }
                s1.data.push_back(*it);
            }
            for(int j=c;j<line.size();j++)
            {
                s1.country.push_back(line[j]);
            }
            Data.push_back(s1);
        }
        return Data;
   }
    void adauga_flights()
    {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
        int z, l, an;
        string country;
        cout<<"Enter the day that you want to submit"<<endl;
        cin>>z;
        try
        {
            if(z<0 || z>31)
            {
              throw "Day format incorrect, try again";
            }
        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
            while(true)
            {
                cin>>z;
                if(z>=1 && z<=31)
                {
                    break;
                }
                cout<<"Day format incorrect, try again"<<endl;
                
            }
        }
        cout<<"Enter the day you want to submit"<<endl;
        cin>>l;
        try
        {
            if(l<0 || l>12)
            {
              throw "Month format incorrect, try again";
            }
        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
            while(true)
            {
                cin>>l;
                if(l>=1 && l<=12)
                {
                    break;
                }
                cout<<"Month format incorrect, try again"<<endl;
                
            }
        }
        cout<<"Enter the year you want to submit"<<endl;
        cin>>an;
        try
        {
            if(an<2021)
            {
              throw "Year format incorrect, try again";
            }
        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
            while(true)
            {
                cin>>an;
                if(an>=2021)
                {
                    break;
                }
                cout<<"Year format incorrect, try again"<<endl;
                
            }
        }
        cout<<"Enter the country you want to submit"<<endl;
        cin>>country;
        int flag1=1;
        if(an>2021)
        {
            flag1 = 1;
        }
        try
        {
            if(an==2021)
            {
                flag1 = 0;
                throw flag1;
            }
        }
        catch(const int msg)
        {
            if(l ==(now->tm_mon+1))
            {
                while(true)
                {
                    if(z<now->tm_mday)
                    {
                        cout<<"Day format incorrect, you put a day from the past, choose another day looking in the calendar"<<endl;
                        cin>>z;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if(l <(now->tm_mon +1))
            {
                while(true)
                {
                    if(l<(now->tm_mon +1))
                    {
                        cout<<"Month format incorrect, you put a month from the past, choose another one looking in the calendar"<<endl;
                        cin>>l;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        try
        {
            for( int i=0;i<country.length();i++)
        {
            if(country[i]<65 || (country[i]>90 && country[i]<97) || country[i]> 122)
            {
                throw "You submitted characters that don't exist in the names of any country";
            }
        }
        }
        catch(const char* msg)
        {
        cerr<<msg<<endl;
        int c=0;
        while(true)
        {
            cout<<"Insert another country"<<endl;
            cin>>country;
            for(int i=0;i<country.size();i++)
            {
                if((country[i]>=65 && country[i]<=90) || (country[i]>=97 && country[i]<=122)) 
                {
                    c++;
                }
            }
            if(c==country.size())
            {
                break;
            }
        }
        }
        ofstream file;
        file.open("flights.csv",ios::app);
        if(file.is_open())
        {
        file<<z<<"/"<<l<<"/"<<an<<","<<country<<"\n";
        }
        file.close();
    }
    void erase_flights()
    {
        vector<infos> V1 = get_info("flights.csv");
        try
        {
        if(V1.size()==0)
        {
            throw "There are no flights, you don't have what to  erase";
        }
        else
        {
        for(auto it =V1.begin();it!=V1.end();it++)
        {
            cout<<it->data<<","<<it->country<<endl;
        }
        cout<<"Enter what line you want to delete"<<endl;
        int option;
        cin>>option;
        if(option>V1.size())
        {
            throw "You want to delete a flight from a line which does not exist, null comamand";
        }
        V1.erase(V1.begin()+(option-1));
        ofstream file;
    file.open("flights.csv");
    for( auto it = V1.begin();it!=V1.end();it++)
    {
        file<<it->data<<","<<it->country<<"\n";
    }
    file.close();
    }
    }
    catch(const char* msg)
    {
        cerr<<msg<<endl;
    }
    }
    void search_flight()
    {
    string data;
    cout<<"Enter the date format for the flight you are looking for:"<<endl;
    cin>>data;
    string country;
    cout<<"Enter in what country is the flight you are looking for:"<<endl;
    cin>>country;
    vector<infos> V1 = get_info("flights.csv");
    for(auto it =V1.begin();it!=V1.end();it++)
    {
        cout<<it->data<<","<<it->country<<endl;
    }
    try
    {
    if(V1.size()==0)
    {
        throw "There are no flights, you don't have where to look";
    }
    else
    {
    for( auto it = V1.begin();it!=V1.end();it++)
    {
        if(it->data == data)
        {
            if(it->country == country)
            {
                cout<<"Searched flight exists"<<endl;
                break;

            }
        }
        else
        {
            throw "Non-existent flight";
        }
    }
    }
    }
    catch(const char* msg)
    {
        cerr<<msg<<endl;
    }
    }
    void rezerva_zbor()
    {
        ofstream file1;
        file1.open("Reserved_flights.csv",ios::app);
        fstream file;
        file.open("flights.csv");
        vector<infos> V1 = get_info("flights.csv");
        try
        {
            if(V1.size()==0)
            {
                throw "There are no flights, you don't have where to look";
            }
            else
            {
            for(auto it =V1.begin();it!=V1.end();it++)
        {
            cout<<it->data<<","<<it->country<<endl;
        }
        cout<<"Enter the line at which the flight that you want to reserve is:"<<endl;
        int reservation;
        cin>>reservation;
        if(reservation>V1.size())
        {
            throw "Non existent flight, you cannot reserve";
        }
        int c=0;
        for( auto it=V1.begin();it!=V1.end();it++)
        {
            c++;
            if(reservation ==c)
            {
                file1<<it->data<<","<<it->country<<"\n";
                break;
            }
        }
            }
        }
        catch(const char* msg)
        {
            cerr<<msg<<endl;
        }
        
    }
    void Permissions()
    {
        int x;
        try
        {
        x = login();
        cout<<"***********************************************************************************************"<<endl;
        if( x==1)
        {
            int flag = 1;
            while(flag == 1)
            {
            cout<<"Press 1 to add a flight and 2 to erase a flight from a particular line in the document"<<endl;
                int choice_1;
                cin>>choice_1;
                if(choice_1 ==1)
                {
                    adauga_flights();
                    cout<<"Do you want to do something else, or to leave?If you want to leave, press 0,if not, press 1"<<endl;
                    cin>>flag;
                }
                if(choice_1 == 2)
                {
                    erase_flights();
                    cout<<"Do you want to do something else, or to leave?If you want to leave, press 0,if not, press 1"<<endl;
                    cin>>flag;
                }
            }
            cout<<"You left the app"<<endl;
        }
        if(x==2)
        {
                        
            int flag = 1;
            while(flag == 1)
            {
            cout<<"Press 1 to search a flightand 2 to reserve a flight from a particular line in the document"<<endl;
                int choice_1;
                cin>>choice_1;
                if(choice_1 ==1)
                {
                    search_flight();
                    cout<<"Do you want to do something else, or to leave?If you want to leave, press 0,if not, press 1"<<endl;
                    int choice_1_2;
                    cin>>choice_1_2;
                    flag = choice_1_2;
                }
                if(choice_1 == 2)
                {
                    rezerva_zbor();
                    cout<<"Do you want to do something else, or to leave?If you want to leave, press 0,if not, press 1"<<endl;
                    int choice_1_2;
                    cin>>choice_1_2;
                    flag = choice_1_2;
            }            
        }
        cout<<"Congratulations, you left the app."<<endl;
        }
        }
        catch(const int msg)
        {
            if( msg == 3)
            {
                cerr<<"Unsuccessful loggin, wrong password. Try again to log in"<<endl;
                Permissions();
            }
            if( msg == 4)
            {
                cerr<<"Unsuccessful loggin, wrong username. Try again to log in"<<endl;
                Permissions();
            }
        }
        return ;
    }
    bool has_ampersand( string x)
    {
        for( int i=0;i<x.length();i++)
        {
            if(x[i]=='@')
            {
                return true;
            }
        }
        return false;
    }     
    bool has_comma(string x)
    {
        for( int i=0;i<x.length();i++)
        {
            if(x[i]==',')
            {
                return true;
            }
        }
        return false;

    }
    void sign_in()
    {
    cout<<"Choose a username"<<endl;
    cout<<"Attention,chosen username must have '@' character, mandatory for an email. It also has not to have space or comma"<<endl;
    getline(cin,Email_Username);
    try{
        if(has_ampersand(Email_Username)==false || has_space_char(Email_Username)== true || has_comma(Email_Username)==true)
        {
            throw false;
        }
    }
    catch( const bool msg)
    {
        cout<<"Wrong username format,try again"<<endl;
        while(true)
        {
        getline(cin,Email_Username);
        if(has_ampersand(Email_Username)==true && has_space_char(Email_Username)==false && has_comma(Email_Username)==false)
        {
            break;
        }
        cout<<"Username format wrong, try again"<<endl;
        }
    }
    cout<<"Attention, the password need to have at least 5 characters, it must not have space or comma, it is necessarry to memorize it"<<endl;
    cout<<"Choose a password"<<endl;
    getline(cin,Pass);
    try
    {
    if(Pass.length()<5)
    {
        throw false;
    }
    }
    catch( const bool msg)
    {
        cout<<"Password too weak,try again"<<endl;
        while(true)
        {
            getline(cin,Pass);
            if(Pass.length()>=5)
            {
                break;
            }
            cout<<"Password too weak, try again"<<endl;
        }
    }
    try
    {
        if(has_comma(Pass) == true || has_space_char(Pass) == true)
        {
            throw 1;
        }
    }
    catch( const int msg)
    {
        while(true)
        {
            cout<<"Wrong password format, it has either a space or comma, try again"<<endl;
            getline(cin,Pass);
            if(has_comma(Pass)==false && has_space_char(Pass) == false)
            {
                break;
            }
        }
    }
    cout<<"Submit the password again"<<endl;
    getline(cin,verify_pass);
    try
    {
        if(verify_pass != Pass)
        {
            throw 1;
        }
    }
    catch(const int msg)
    {
        cout<<"Re-submitted password wrong, try again."<<endl;
        while(true)
        {
            cin>>verify_pass;
            if(Pass == verify_pass)
            {
                break;
            }
            cout<<"Re-submitted password wrong, try again."<<endl;
        }
    }
    ofstream file;
    file.open("Users.csv",ios::app);
    vector<int> crip_pass_user = encryption(Pass);
    if(file.is_open())
    {
        file<<Email_Username<<",";
        for(auto it =crip_pass_user.begin();it!=crip_pass_user.end();it++)
        {
            file<<(*it);
            if(next(it)!=crip_pass_user.end())
        {
            file<<",";
        }
        }
        file<<"\n";
    }
    file.close();
    }
};
int main()
{
    Try_Sign_in obj1;
    ofstream file;
    file.open("Operators.csv");
    vector<int> Vector1 = obj1.encryption("Pass1");
    vector<int> Vector2 = obj1.encryption("Pass2");
    if(file.is_open())
    {
    file<<"Operator1"<<",";
    for( auto it = Vector1.begin();it!=Vector1.end();it++)
    {
        file<<(*it);
        if(next(it)!=Vector1.end())
        {
            file<<",";
        }
    }
    file<<"\n"<<"Operator2"<<",";
    for(auto it = Vector2.begin();it!=Vector2.end();it++)
    {
        file<<(*it);
        if(next(it)!=Vector2.end())
        {
            file<<",";
        }
    }
    }
    file.close();    
    cout<<"***********************************************************"<<endl;
    obj1.sign_in();
    obj1.Permissions();
    return 0;
}
