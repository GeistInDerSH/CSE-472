#ifndef __READCSV_H__
#define __READCSV_H__

#include <algorithm>
#include <cctype>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "enable_debug.h"

typedef enum related
{
	UNSET = 0,
	AGREE,
	DISAGREE,
	UNRELATED
} Related_t;

typedef struct string_count
{
	std::string str = "";
	int count = 0;
} StringCount_t;

/**
 * Class for storing data on what is being compared
 */
class Compare
{
	public:
		Compare( int id, int title_id1, int title_id2,
				std::string title1, std::string title2 );
		Compare( int id, Related_t related );
		~Compare();

		Related_t get_related();
		int get_id();
		int get_title1_id();
		int get_title2_id();
		std::string get_title1();
		std::string get_title2();

		void begin_comparison();
		void print_output();

#ifdef ACCURACY
		bool get_accuracy( std::vector<Compare *> accuracy_vector );
#endif

#ifdef DEBUG
		void print_debug();
#endif

	private:
		Related_t are_related;
		int id;
		int title_id1;
		int title_id2;
		std::string title1;
		std::string title2;

		std::string string_cleanup( std::string str );
		std::string punctuation_cleanup( std::string str );
		std::string replace_and( std::string str );
		std::string article_cleanup (std::string str );
		std::string remove_double_space( std::string str );

		std::vector<StringCount_t *> generate_unique( std::string str );

		Related_t compare_vectors( std::vector<StringCount_t *> vector_1,
									std::vector<StringCount_t *> vector_2 );
};

/**
 * Class for reading in from the CSV file to allow for the data to be
 * more easily read by the computer
 */
class ReadCSV
{
	public:
		ReadCSV(std::string file_name);
		~ReadCSV();

		void start_file_parsing();

		std::vector<Compare *> get_compare_vector();

#ifdef ACCURACY
		void load_validation();
		std::vector<Compare *> get_accuracy_vector();
#endif
	private:
		std::string file_name;
		std::vector<Compare *> compare_vector;
#ifdef ACCURACY
		std::vector<Compare *> accuracy_vector;
		Compare *generate_accuracy( std::string line );
#endif
		Compare* generate_object( std::string line );
		std::string to_lowercase( std::string str );
		void main_parser();

};
#endif
