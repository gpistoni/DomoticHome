#pragma  once
#include <fstream>
#include <string>
#include <vector>
#include "SLibraries/SBase/string/SString.h"

class  CSCsvTable
{
	CSString m_fileName;
	char m_valueSeparator;

	std::vector<std::vector<std::string>> m_data;

public:
	CSCsvTable (CP_CSString fileName, char valueSeparator = ','  )
	{
		m_fileName = fileName;
		m_valueSeparator = valueSeparator;
	}
	
	~CSCsvTable ( )
	{
	}

	size_t rows()
	{
		return m_data.size();
	};

	size_t cols(size_t r)
	{
		if ( r<rows() ) 
			return m_data[r].size();
	};

	CSString Get( int row, int col );
	void Set( int row, int col, CSString value );

public:	
	void Read( );
	void Write( );
};
