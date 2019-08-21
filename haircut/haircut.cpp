#include <iostream>
#include <algorithm>
#include <cctype>//this two libraries helps in trimming strings 
#include <locale>
#include  <boost/algorithm/string.hpp>//trims strings with spaces


using namespace std;


class haircut
{
	private:
		string service_type;
		string customer_type;
                int charges , charge;
		int amount_tendered;
		int total_kubwa_charge = 0;
		int total_ndogo_charge = 0;
	public:
		int getKubwa () { return total_kubwa_charge; }
		int getNdogo() { return total_ndogo_charge; }
		void getData()
		{  
			while(1)
			{
			cin.ignore(256 , '\n');//enables change of streams
			cout  << "Service type(ndogo/ kubwa) : ";
			getline(cin , service_type);
			//trim spaces
			boost::trim_right(service_type);
			boost::trim_left(service_type);
			for_each(service_type.begin(), service_type.end()  ,[](char& c) { c=::tolower(c);});//this converts  the string into lower case
			if(service_type == "x")
			{
				break;
			}
			cout << "Customer Type( regular / new): " ;
			cin >>  customer_type;
			//trim spaces 
			boost::trim_right(customer_type);
			boost::trim_left(customer_type);
			//converts to lower case  
			for_each(customer_type.begin() , customer_type.end() , [](char& c) { c =::tolower(c); });
			
			charge = Charges(service_type , customer_type);
			cout << "Serice type: " << service_type << "\n Customer Type : " << customer_type << "\n  Charges: " <<  charge << endl;
			cout << "Amount tendered : ";
			cin >> amount_tendered;
                	cout << "Serice type: " << service_type << "\n Customer Type : " << customer_type << "\n  Charges: " <<  charge << "\n Amount tendered: " << amount_tendered <<  endl;
			cout << "\n\n Balance: " << amount_tendered- charge << endl;
			}

		}
		int  Charges(string service_type, string customer_type)
		{
			if(service_type == "ndogo")
			{
				if(customer_type == "regular")
				{
					charges = 55;	// charges for a regular customer
					total_ndogo_charge += 55; 

				}
				else if(customer_type == "new")
				{
					charges = 80;//charges for a new customer
					total_ndogo_charge += 80;
				}
				else
				{
					charges = 0;//charges in case of error
				}
			}
			else if ( service_type == "kubwa")
			{
				charges = 470;//charges for big services
				total_kubwa_charge += 470;
			}
			else
			{
				charges = 0;
			}
			return charges;
		}
};
int main()
{
	haircut hair;
	hair.getData();
	cout << "kubwa Service: " << hair.getKubwa() << endl;
	cout << "Ndogo Service: " << hair.getNdogo() << endl;
	return 0;
}
