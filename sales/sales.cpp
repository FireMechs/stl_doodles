#include <iostream>
#include <string>

using namespace std;

class sales
{
	private:
		string name;//name  of the sales person
		char Rsale;//stands for the region of sale
		int  Nunits;//number of units 
		int  price = 1400;//the price of each unit
		float total_sale;//gross the sales amount
		float com_tax;//commission tax
		float commission;//commission
		int  sales_X = 0 , sales_Y = 0 , sales_Z = 0;//sums  of the sales in each region
		float net_commission;//takes the net commissions
	public:
		/*return  private total_sales */
		float  getSales_X(){   return sales_X; }
		float  getSales_Y() { return sales_Y; }
		float getSales_Z() { return sales_Z; }
		//end of the return 
		void getData()
		{
			cin.ignore(256,'\n'); //enable change  of streams without skips
			cout << "\t Enter salesPerson name: " ;
			getline(cin, name);//able to get the spaces  between the strings
			cout << "\t Enter region of sale(x/y/z): ";
			cin >> Rsale;
			cout << "\t Enter number of units sold: ";
			cin  >> Nunits;
			handleTax(Rsale ,Nunits);
			char ch;
			cout << "\t\t Another SP(y/n): " ;
			cin >> ch;
			if(ch == 'y' || ch == 'Y')
			{
				getData();
			}
			else
			{}
		}
		void handleTax(char region , int units)
		{
			total_sale = units * price;//gross sales amount 
			if (region == 'x' || region == 'X')
			{
			    sales_X += total_sale;
			    commission = (0.15 * (float)total_sale);//typecasting the integer total_sale variable to avoid the int*float error 
		            float temp1 = comTax(commission);
                            cout << "Name: " << name << " | Region: " <<  region <<" | No of sale: " << units << " | Sales value: " << total_sale << " | Net sale commission: " << temp1 << endl; 			}
			else if( region == 'y' || region == 'Y')
			{
				sales_Y += total_sale;
				commission = (0.18 * (float) total_sale);
				float temp2 = comTax(commission);
				cout << "Name: " << name << " | Region: " <<  region <<" | No of sale: " << units << " | Sales value: " << total_sale << " | Net sale commission: " << temp2 << endl; 
			}
			else if(region == 'z' || region == 'Z')
			{
			      sales_Z += total_sale;
			      commission = (0.19 * (float) total_sale);//gross  commission 
			      float temp3 = comTax(commission);//net commission
			      /*gather for  units  > 300 in the Z region */
			      if(units > 300)
			      {
				      float extra_comm = (0.1 * (float) price) * ((units - 300));
				      temp3 += extra_comm;
			      }
			      cout << "Name: " << name << " | Region: " <<  region <<" | No of sale: " << units << " | Sales value: " << total_sale << " | Net sale commission: " << temp3 << endl; 
			}
			else
			{
				cerr << "Error! , check on the elements " << endl;//print  an error message
			}
		}
		float comTax(float com)
		{
			if (com >= 25000)
			{
				com_tax = (0.10 * com);
				net_commission = com - com_tax;
			}
			else
			{
				com_tax = 0;
				net_commission = com - com_tax;
			}
			return net_commission;
		}
};
int main()
{
	sales sp;//objects of the class
        cout << "\t\t\t\t ABC " << endl;
	sp.getData();
	//now its time to display the total sales per region
	cout << "\n\t\t\t Total sales " << endl;
	cout << "Region X: " << sp.getSales_X() << "\n Region Y: " << sp.getSales_Y() << "\n Region Z: " << sp.getSales_Z() << endl;
	return 0;
}
