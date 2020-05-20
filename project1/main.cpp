#include <cstdio>
#include <string>

#include "compare.h"
#include "enable_debug.h"

void print_help()
{
	printf("\t---Help Menu---\n");
	printf("\tThis program takes a single argument when running.\n");
	printf("\tSaid argument should be the name of the CSV file that\n");
	printf("\tyou wish to analize. Please include the full name of\n");
	printf("\tthe file\n");
	printf("\te.g. ./comparison test.csv\n");
}

int main(int argn, char** args)
{
	if( argn != 2 )
	{
		print_help();
		exit(1);
	}
	std::string str( args[1] );
	ReadCSV *csv = new ReadCSV( str );
	std::vector<Compare *> compare_vector;

	csv->start_file_parsing();

	compare_vector = csv->get_compare_vector();

#ifndef DEBUG
#ifndef ACCURACY
	printf("id,label\n");
#endif
#endif

	for( Compare *compare : compare_vector )
	{
		compare->begin_comparison();
#ifdef DEBUG
		compare->print_debug();
#endif
#ifndef ACCURACY
		compare->print_output();
#endif
	}

#ifdef ACCURACY
	int total_count;
	int total_match = 0;
	std::vector<Compare *> accuracy;

	accuracy = csv->get_accuracy_vector();
	total_count = accuracy.size();

	for( Compare *compare : compare_vector )
	{
		bool are_same = compare->get_accuracy( accuracy );
		if( are_same )
		{
			++total_match;
		}
	}

	printf("Count: %d\nMatch: %d\n", total_count, total_match);

	double percent_accurate = (double) total_match / total_count;
	printf("Accuracy: %f%%\n", 100 * percent_accurate );
#endif

	return 0;
}
