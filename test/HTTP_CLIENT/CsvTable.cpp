#include "CsvTable.h"


CSString CSCsvTable::Get( int row, int col )
{
	if ( m_data.size()< row+1 )			m_data.resize(row+1);
	if ( m_data[row].size()< col+1 )	m_data[row].resize(col+1);
	return m_data[row][col];
}

void CSCsvTable::Set( int row, int col, CSString value )
{
	if ( m_data.size()< row+1 )			m_data.resize(row+1);
	if ( m_data[row].size()< col+1 )	m_data[row].resize(col+1);
	m_data[row][col] = value;
}

void CSCsvTable::Read()
{
	std::ifstream file(m_fileName);
	CSString separator;
	separator.push_back(m_valueSeparator);

	int row=0;
	while( !file.eof() )
	{			
		CSString line;
		std::getline(file, line);
		if ( !file.good() ) 
			break;

		CSStringVector values;
		line.SplitTo( values, separator.c_str() );
		int col=0;
		for (auto var: values )
		{
			Set(row, col, var);
			col++;
		}
		row++;
	}
}

void CSCsvTable::Write()
{
	std::ofstream file(m_fileName);

	for (int row=0; row<m_data.size(); row++)
	{
		for (int col=0; col< m_data[row].size(); col++)
		{
			file << m_data[row][col] << m_valueSeparator ;
		}
		file << "\n";
	}
	file.flush();
}
