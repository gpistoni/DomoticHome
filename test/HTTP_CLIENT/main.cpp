#include <vector>

#include "HttpClient.h"
#include "CsvTable.h"

///////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	CSString host = "it.exchange-rates.org"; 

	CSCsvTable table("c:/tab.csv",';');
	table.Read();

	for (int j=1; j<table.rows(); j++)
	{
		bool modified= false;
		for ( int i=1; i<table.cols(0); i++ )
		{
			if ( table.Get(j, i).empty() )
			{
				CSString seme = table.Get(0,i);
				CSString data = table.Get(j,0);
				data.Replace("/","-");

				CSString path = "/Rate/EUR/" + seme + "/" + data;
				CHTTPClient http;

				CSString str = http.Request( host, path );
				CSString search = seme +  "</td><td class=\"text-nowrap text-narrow-screen-wrap\">";

				if ( str.size() > 100 )
				{
					size_t pos = str.Find( search, 0 ) + search.size() ;
					CSString str2 = str.substr( pos, 10 );
					std::cout << data << ": " << str2 << std::endl;

					pos = str2.find_first_of(" ");
					if (pos > 0)
					{
						str2.erase(pos + 1);
					}

					if (str2.size() > 4)
						table.Set(j, i, str2);	
					else
						table.Set(j, i, "");
					modified = true;
				}
			}
		}

		if ( modified ) table.Write();
	}

	int i;
	std::cin >> i;

	return 0;
};

