#include <iostream>
#include  <string>
#include <vector>

int main()
{
	std::string input;
	std::cout  << "Decimal fraction to convert: ";
	std::cin  >> input;
   
    std::size_t  pos = input.find('.');
    //vector to store the binary values before and after the decimal point 
    std::vector<int> vec_num_b4_dec;
    std::vector<int> vec_num_aft_dec;

    if(pos != std::string::npos )
    {
    	//decimal point found continue with the computation 
        std::string after_decimal = input.substr(pos);
        std::string before_decimal = input.substr(0,pos);
        std::cout << before_decimal << "	"<<  after_decimal << std::endl;
        // convert both to integers
        auto n_before_decimal = std::stoi(before_decimal);
        float n_after_decimal  = std::stof(after_decimal);

        // using lambdas find the binary equivalent of the values obtained
        auto result_bin_before_decimal = [&n_before_decimal,&vec_num_b4_dec]() // capture the values by values coz we will not be changing them instead
        {
        	while (n_before_decimal != 0)
        	{
        		int rem_bin = n_before_decimal % 2;
        		vec_num_b4_dec.push_back(rem_bin);
        		auto bin = n_before_decimal / 2; // quotient
        		--n_before_decimal;
        	}
        };


        auto result_bin_after_decimal = [&n_after_decimal,&vec_num_aft_dec]()
        {
        	for(int i = 0; i < 6; ++i)
        	{
        		auto val = n_after_decimal * 2;
        		auto num_dec = [&val , &vec_num_aft_dec]()
        		{
        			std::string return_forLoop;
        			std::string val_string = std::to_string(val);
        			std::size_t  pos = val_string.find('.');
        			if(pos != std::string::npos)
        			{
        			    std::string after_decimal = val_string.substr(pos);
        			    std::string before_decimal =  val_string.substr(0,pos);
        			    int num = std::stoi(before_decimal);
        			    int num_div = num / 2;
        				int num_rem = num % 2;
        				if ((num_div == 0 || num_div == 1) && (num_rem >= 0) )
        				{
        					if(num%2 == 0)
        						vec_num_aft_dec.push_back(0);
        					else
        						vec_num_aft_dec.push_back(1);
        				}

        				return_forLoop = after_decimal.insert(0,"0");
        			}
        			else
        			{
        				std::cout << "Decimal not found" << std::endl;
        			}
        			auto return_val = std::stof(return_forLoop);
        			return return_val;
        		};

        		n_after_decimal = num_dec();
        	}
        };
                /*vector to store the binary values for number b4 and 1/2t the  decimal*/
        result_bin_before_decimal();
        result_bin_after_decimal();
    }
    else
    {
    	std::cout << "Error, input is in wrong format" << std::endl;
    }
    for(std::size_t  i = 0 ; i < vec_num_b4_dec.size();++i)
	   std::cout << vec_num_b4_dec[i];
    std::cout <<"***********" <<std::endl;
    for(std::size_t j =0 ; j < vec_num_aft_dec.size();++j)
	    std::cout << vec_num_aft_dec[j];
    std::cout << std::endl;
    return 0;
}
