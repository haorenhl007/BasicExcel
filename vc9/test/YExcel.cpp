#include <BasicExcel.hpp>
using namespace YExcel;

int main(int argc, char* argv[])
{
	BasicExcel e;

	// Load a workbook with one sheet, display its contents and save into another file.
	e.Load("example1.xls");	
	BasicExcelWorksheet* sheet1 = e.GetWorksheet("Sheet1");
	if (sheet1)
	{
		size_t maxRows = sheet1->GetTotalRows();
		size_t maxCols = sheet1->GetTotalCols();
		cout << "Dimension of " << sheet1->GetAnsiSheetName() << " (" << maxRows << ", " << maxCols << ")" << endl;

		printf("          ");
		for (size_t c=0; c<maxCols; ++c) printf("%10d", c+1);
		cout << endl;

		for (size_t r=0; r<maxRows; ++r)
		{
			printf("%10d", r+1);
			for (size_t c=0; c<maxCols; ++c)
			{
				BasicExcelCell* cell = sheet1->Cell(r,c);
				switch (cell->Type())
				{
					case BasicExcelCell::UNDEFINED:
						printf("          ");
						break;

					case BasicExcelCell::INT:
						printf("%10d", cell->GetInteger());
						break;

					case BasicExcelCell::DOUBLE:
						printf("%10.6lf", cell->GetDouble());
						break;

					case BasicExcelCell::STRING:
						printf("%10s", cell->GetString());
						break;

					case BasicExcelCell::WSTRING:
						wprintf(L"%10s", cell->GetWString());
						break;
				}
			}
			cout << endl;
		}
	}
	cout << endl;
	e.SaveAs("example2.xls");

	// Create a new workbook with 2 worksheets and write some contents.
	e.New(2);
	e.RenameWorksheet("Sheet1", "Test1");
	BasicExcelWorksheet* sheet = e.GetWorksheet("Test1");
	BasicExcelCell* cell;
	if (sheet)
	{
		for (size_t c=0; c<4; ++c)
		{
			cell = sheet->Cell(0,c);
			cell->Set((int)c);
		}

		cell = sheet->Cell(1,3);
		cell->SetDouble(3.141592654);

		sheet->Cell(1,4)->SetString("Test str1");
		sheet->Cell(2,0)->SetString("Test \" str2");
		sheet->Cell(2,5)->SetString("Test str1");

		sheet->Cell(4,0)->SetDouble(1.1);
		sheet->Cell(4,1)->SetDouble(2.2);
		sheet->Cell(4,2)->SetDouble(3.3);
		sheet->Cell(4,3)->SetDouble(4.4);
		sheet->Cell(4,4)->SetDouble(5.5);

		sheet->Cell(4,4)->EraseContents();
	}

	sheet = e.AddWorksheet("Test2", 1);
	sheet = e.GetWorksheet(1); 
	if (sheet)
	{
		sheet->Cell(1,1)->SetDouble(1.1);
		sheet->Cell(2,2)->SetDouble(2.2);
		sheet->Cell(3,3)->SetDouble(3.3);
		sheet->Cell(4,4)->SetDouble(4.4);
		sheet->Cell(70,2)->SetDouble(5.5);
	}
	e.SaveAs("example3.xls");

	// Load the newly created sheet and display its contents
	e.Load("example3.xls");

	size_t maxSheets = e.GetTotalWorkSheets();
	cout << "Total number of worksheets: " << e.GetTotalWorkSheets() << endl;
	for (size_t i=0; i<maxSheets; ++i)
	{
		BasicExcelWorksheet* sheet = e.GetWorksheet(i);
		if (sheet)
		{
			size_t maxRows = sheet->GetTotalRows();
			size_t maxCols = sheet->GetTotalCols();
			cout << "Dimension of " << sheet->GetAnsiSheetName() << " (" << maxRows << ", " << maxCols << ")" << endl;

			if (maxRows>0)
			{
				printf("          ");
				for (size_t c=0; c<maxCols; ++c) printf("%10d", c+1);
				cout << endl;
			}

			for (size_t r=0; r<maxRows; ++r)
			{
				printf("%10d", r+1);
				for (size_t c=0; c<maxCols; ++c)
				{
					cout << setw(10) << *(sheet->Cell(r,c));	// Another way of printing a cell content.				
				}
				cout << endl;
			}
			if (i==0)
			{
				ofstream f("example4.csv");
				sheet->Print(f, ',', '\"');	// Save the first sheet as a CSV file.
				f.close();
			}
		}
		cout << endl;
	}

    system("pause");
	return 0;
}
