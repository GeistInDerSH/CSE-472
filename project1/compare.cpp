#include "compare.h"

/* Compare Class Functions */

/**
 * Public constructor for the compare class. It takes the id line, the title id values
 * for the two titles that are being compared and the two titles that are going
 * to be compared.
 */
Compare::Compare( int id, int title_id1, int title_id2, std::string title1,
				  std::string title2 )
{
	this->id = id;
	this->title_id1 = title_id1;
	this->title_id2 = title_id2;
	this->title1 = title1;
	this->title2 = title2;
	this->are_related = UNSET;
}

Compare::Compare( int id, Related_t related )
{
	this->id = id;
	this->title_id1 = -1;
	this->title_id2 = -1;
	this->title1 = "";
	this->title2 = "";
	this->are_related = related;
}

/**
 * Public deconstructor for the compare class. All of the variables are reset to
 * negative one if they are an int or to an empty string if they are a string.
 */
Compare::~Compare()
{
	id = -1;
	title_id1 = -1;
	title_id2 = -1;
	title1 = "";
	title2 = "";
	are_related = UNSET;
}

Related_t Compare::get_related()
{
	return are_related;
}

int Compare::get_id()
{
	return id;
}

int Compare::get_title1_id()
{
	return title_id1;
}

int Compare::get_title2_id()
{
	return title_id2;
}

std::string Compare::get_title1()
{
	return title1;
}

std::string Compare::get_title2()
{
	return title2;
}

/**
 * Begin comparing the two titles. First clean up the two strings
 * by removing any unneeded things (punctuation, etc.) then compare
 * the resutls
 */
void Compare::begin_comparison()
{
#ifdef STUPID_MODE
	srand(time(NULL) + rand());
	switch ( (rand() % 3) + 1 )
	{
		case 1:
			are_related = AGREE;
			break;
		case 2:
			are_related = DISAGREE;
			break;
		case 3:
			are_related = UNRELATED;
			break;
	}
	return;
#else

	title1 = string_cleanup( title1 );
	title2 = string_cleanup( title2 );

	std::vector<StringCount_t *> title1_unique;
	std::vector<StringCount_t *> title2_unique;

	title1_unique = generate_unique( title1 );
	title2_unique = generate_unique( title2 );

#ifdef DEBUG
	printf("Vector 1:\n");
	for( StringCount_t *sc : title1_unique )
	{
		printf("\t%s\t%d\n", sc->str.c_str(), sc->count);
	}

	printf("Vector 2:\n");
	for( StringCount_t *sc : title2_unique )
	{
		printf("\t%s\t%d\n", sc->str.c_str(), sc->count);
	}
#endif

	are_related = compare_vectors( title1_unique, title2_unique );

#endif
}

/**
 * Print the result of the test in the format that the graders want
 */
void Compare::print_output()
{
	std::string status = "";
	switch(are_related)
	{
		case 1:
			status = "agreed";
			break;
		case 2:
			status = "disagreed";
			break;
		case 3:
			status = "unrelated";
			break;
		default:
			status = "ERROR: Unset";
			break;
	}

	printf("%d,%s\n", id, status.c_str());
}

#ifdef ACCURACY
/**
 * Checks the current compare object against all items in the passed vector
 * if the id number and expected result are the same then return true
 */
bool Compare::get_accuracy(std::vector<Compare *> accuracy_vector)
{
	for( Compare *compare : accuracy_vector )
	{
		if( id == compare->get_id() )
		{

#ifdef DEBUG
			printf("%d == %d\n", id, compare->get_id());
#endif
			if( are_related == compare->get_related() )
			{
#ifdef DEBUG
				printf("%d --vs-- %d\n", id, compare->get_id());
#endif
				return true;
			}
		}
	}
	return false;
}
#endif

#ifdef DEBUG
/**
 * Prints internal debug information on the data stored within
 * the variables in the compare object
 */
void Compare::print_debug()
{
	printf("id:%d\n", id);
	printf("Title id 1:%d\n", title_id1);
	printf("Title id 2:%d\n", title_id2);
	printf("Title 1:%s\n", title1.c_str());
	printf("Title 2:%s\n", title2.c_str());
	printf("\n");
}
#endif

/* Private Compare Class Functions */

/**
 * Cleanup the given string by removing punctuation, replacing symbols
 * with and, removing articles, and removing double spaces
 */
std::string Compare::string_cleanup( std::string str )
{
	str = punctuation_cleanup( str );
	str = replace_and( str );
	str = article_cleanup( str );
	str = remove_double_space( str );
	return str;
}

/**
 * Remove any special characters
 */
std::string Compare::punctuation_cleanup( std::string str )
{
	if( str.at(0) == '"')
	{
		str.replace(str.begin(), str.begin()+1, " ");
	}

	if( str.at(str.length() - 1) == '"')
	{
		str.replace(str.end()-1, str.end(), " ");
	}

	str.erase( std::remove(str.begin(), str.end(), ','), str.end());
	str.erase( std::remove(str.begin(), str.end(), '"'), str.end());
	str.erase( std::remove(str.begin(), str.end(), '.'), str.end());
	str.erase( std::remove(str.begin(), str.end(), '!'), str.end());
	str.erase( std::remove(str.begin(), str.end(), '?'), str.end());
	str.erase( std::remove(str.begin(), str.end(), ':'), str.end());

	return str;
}

/**
 * Replace characters that are commonly used a and in short-hand
 * with the word and
 */
std::string Compare::replace_and( std::string str )
{
	int location;
	location = str.find(" & ");
	if( location >= 0 )
	{
		str.erase( std::remove(str.begin(), str.end(), '&'), str.end());
		str.replace(str.begin() + location, str.begin()+ location +1, " and");
	}

	location = str.find(" + ");
	if( location >= 0 )
	{
		str.erase( std::remove(str.begin(), str.end(), '+'), str.end());
		str.replace(str.begin() + location, str.begin()+ location +1, " and");
	}
	return str;
}

/**
 * Remove any english articles from the string
 */
std::string Compare::article_cleanup( std::string str )
{
	std::string string_array[] = {" a ", " an ", " the ",
									" one ", " some ", " few "};

	for( int i = 0; i < 6; ++i )
	{
		int location;
		while( true )
		{
			location = str.find(string_array[i]);
			if( location >= 0 )
			{
				str.replace(str.begin()+location,
						str.begin()+location+string_array[i].length(),
						" ");
			}
			else
			{
				break;
			}
		}
	}
	return str;
}

/**
 * Remove all instances of two back to back spaces
 */
std::string Compare::remove_double_space( std::string str )
{
	int location;
	while( true )
	{
		location = str.find("  ");
		if( location >= 0 )
		{
			str.replace(str.begin()+location,
						str.begin() + location + 2,
						" ");
		}
		else
		{
			break;
		}
	}
	return str;
}

/**
 * Takes a string as an input an returns a vector of StringCount_t that
 * has the string and the number of times that it apears in the vector.
 * Any duplicate strings are removed
 */
std::vector<StringCount_t *> Compare::generate_unique( std::string str )
{
	std::vector<std::string> string_vector;
	std::istringstream iss(str);

	copy( std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			back_inserter(string_vector) );

	sort( string_vector.begin(), string_vector.end() );

	std::vector<StringCount_t *> return_vector;
	for( std::string s : string_vector )
	{
		if( return_vector.size() == 0 )
		{
			StringCount_t *add = new StringCount_t();
			add->str = s;
			add->count = 1;

			return_vector.push_back(add);
		}
		else
		{
			bool was_added = false;
			for( StringCount_t *compare : return_vector )
			{
				if( s == compare->str )
				{
					was_added = true;
					++compare->count;
				}
			}

			if( !was_added )
			{
				StringCount_t *add = new StringCount_t();
				add->str = s;
				add->count = 1;

				return_vector.push_back(add);
			}
		}
	}

	return return_vector;
}

/**
 * Compares the two passed vectors to check how similar they are
 */
Related_t Compare::compare_vectors( std::vector<StringCount_t *> vector_1,
									std::vector<StringCount_t *> vector_2 )
{
	int total_words = 0;
	int overlap = 0;

	bool sc1_has_not = false;
	bool sc2_has_not = false;
	for( StringCount_t *sc1 : vector_1 )
	{
		total_words += sc1->count;
		sc1_has_not = ( sc1->str == "not" ) ? true : sc1_has_not;
		for( StringCount_t *sc2 : vector_2 )
		{
			if( sc1->str == sc2->str )
			{
				overlap += sc1->count + sc2->count;
				sc2_has_not = ( sc2->str == "not" ) ? true : sc2_has_not;
			}
		}
	}

	for( StringCount_t *sc2 : vector_2 )
	{
		total_words += sc2->count;
	}

	double percent_overlap;
	percent_overlap = (double) overlap / total_words;

	if( percent_overlap > 0.50 )
	{
		if(( !sc1_has_not && !sc2_has_not )
			|| ( sc1_has_not && sc2_has_not ))
		{
			return AGREE;
		}
		else
		{
			return DISAGREE;
		}
	}
	else
	{
		return UNRELATED;
	}
}

/* ReadCSV Class Functions */

/**
 * Default constructor for the ReadCSV class
 * Sets the private file name to be the given file name
 */
ReadCSV::ReadCSV( std::string file_name )
{
	this->file_name = file_name;
}

/**
 * Dealocate all memory used by the compare class objects
 */
ReadCSV::~ReadCSV()
{
	for( Compare *compare : compare_vector )
	{
		delete compare;
	}
}

/**
 * Begin reading the given file
 */
void ReadCSV::start_file_parsing()
{
	main_parser();
}

/**
 * Return the vector of compare objects
 */
std::vector<Compare *> ReadCSV::get_compare_vector()
{
	return compare_vector;
}

#ifdef ACCURACY
/**
 * Returns the accuracy vector containing the id and expected result
 * of the comparison
 */
std::vector<Compare *> ReadCSV::get_accuracy_vector()
{
	return accuracy_vector;
}
#endif

/* Private Functions */

/**
 * Helper function for parsing data into a compare object. If the line is the
 * first line in the file, one without any int values, then return NULL
 */
Compare *ReadCSV::generate_object( std::string line )
{

	std::vector<std::string> read_vector;
	const char *c_str = line.c_str();
	bool is_in_string{false};

	for( const char*c = c_str; *c; c++ )
	{
		if( *c == '"' )
		{
			is_in_string = !is_in_string;
		}
		else if( *c == ',' && !is_in_string )
		{
			read_vector.push_back(std::string(c_str,c-c_str));
			c_str=c+1;
		}
	}
	read_vector.push_back(c_str);

	if( read_vector.size() <= 6 ) { return NULL; }

	std::string id_str;
	std::string tid1_str;
	std::string tid2_str;
	std::string title1;
	std::string title2;

	id_str = read_vector.at(0);
	tid1_str = read_vector.at(1);
	tid2_str = read_vector.at(2);
	title1 = read_vector.at(5);
	title2 = read_vector.at(6);

	title1 = to_lowercase( title1 );
	title2 = to_lowercase( title2 );

	int id;
	int tid1;
	int tid2;

	try
	{
		id = stoi(id_str);
		tid1 = stoi(tid1_str);
		tid2 = stoi(tid2_str);
	}
	catch(std::invalid_argument const &e)
	{
#ifdef DEBUG
		printf("Could not cast STR to INT\n\n");
#endif
		return NULL;
	}

	return new Compare(id, tid1, tid2, title1, title2);
}

#ifdef ACCURACY
/**
 * Helper function for parsing data into a compare object. If the line is the
 * first line in the file, one without any int values, then return NULL
 */
Compare *ReadCSV::generate_accuracy( std::string line )
{

	std::vector<std::string> read_vector;
	const char *c_str = line.c_str();
	bool is_in_string{false};

	for( const char*c = c_str; *c; c++ )
	{
		if( *c == '"' )
		{
			is_in_string = !is_in_string;
		}
		else if( *c == ',' && !is_in_string )
		{
			read_vector.push_back(std::string(c_str,c-c_str));
			c_str=c+1;
		}
	}
	read_vector.push_back(c_str);

	if( read_vector.size() <= 7 ) { return NULL; }

	std::string id_str;
	std::string related_str;
	id_str = read_vector.at(0);
	related_str = read_vector.at(7);

	int id;

	try
	{
		id = stoi(id_str);
	}
	catch(std::invalid_argument const &e)
	{
#ifdef DEBUG
		printf("Could not cast STR to INT\n\n");
#endif
		return NULL;
	}

	if( related_str.at(related_str.length()-1) == ',' )
	{
		related_str = related_str.substr( 0, related_str.length()-2);
	}

	Related_t related;
	if( related_str == "agreed" ) { related = AGREE; }
	else if( related_str == "disagreed" ) { related = DISAGREE;	}
	else if( related_str == "unrelated" ) { related = UNRELATED; }
	else { related = UNSET; }

	return new Compare(id, related);
}
#endif

/**
 * Comvert the string to lowercase
 */
std::string ReadCSV::to_lowercase( std::string str )
{
	std::transform( str.begin(), str.end(), str.begin(),
					[](unsigned char c){ return std::tolower(c); });
	return str;
}

/**
 * Parse the file that was given as a comand line argument. Read in the data
 * using getline and parse the line into a Compare class object using the
 * generate_object helper function
 */
void ReadCSV::main_parser()
{
	std::ifstream file;
	std::string line;

	file.open(file_name);

	if(!file)
	{
#ifdef DEBUG
		printf("Failed to open file: %s\n", file_name.c_str());
#endif
		exit(1);
	}

	while( std::getline(file, line) )
	{
		Compare *compare = generate_object(line);

		if( compare != NULL )
		{
			compare_vector.push_back(compare);

#ifdef DEBUG
			compare->print_debug();
#endif
		}
	}
	file.close();

#ifdef ACCURACY
	file.open(file_name);

	if(!file)
	{
#ifdef DEBUG
		printf("Failed to open file: validataion.csv");
#endif
		exit(1);
	}

	while( std::getline(file, line) )
	{
		Compare *compare = generate_accuracy(line);

		if( compare != NULL )
		{
			accuracy_vector.push_back(compare);
		}
	}
	file.close();
#endif
}

