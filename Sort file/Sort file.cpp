#include <iostream>
#include <FileTapeLibrary.h>
#include <fstream>

bool sort_policy(FileTapeLibrary::ArrayRecord ar1, FileTapeLibrary::ArrayRecord ar2) {
	return ar1.max() <= ar2.max();
}

int main(int argc, char** argv) {
	auto filepath = std::string("./data/input.dat");
	auto output_path = std::string("./data/sorted.dat");
	auto user_input_path = std::string("./data/input.txt");
	auto log_path = std::string("./data/log.log");
	auto log = std::ofstream(log_path, std::ios_base::binary);
	
	if (argc > 1) {
		filepath = std::string(argv[1]);
	}
	else {
		//FileTapeLibrary::convert_to_coded_format(user_input_path, filepath);
		FileTapeLibrary::initialize_random_tape(filepath, 10, 12);
	}

	
	std::cout << "File before:" << std::endl;
	FileTapeLibrary::print_file(filepath);
	auto numbers = polyphase_merge_sort(filepath, output_path, sort_policy, log);
	std::cout << "File after sort:" << std::endl;
	FileTapeLibrary::print_file(output_path);
	
	std::cout << "Number of phases: " << std::get<0>(numbers) << std::endl;
	std::cout << "Number of read/write operations: " << std::get<1>(numbers) << std::endl;
}