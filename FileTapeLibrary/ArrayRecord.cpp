#include "ArrayRecord.h"

#include <string>

FileTapeLibrary::ArrayRecord FileTapeLibrary::ArrayRecord::DNEArrayRecord() {
	return ArrayRecord(0);
}

FileTapeLibrary::ArrayRecord::ArrayRecord(std::size_t size) {
	data = std::vector<int>(size);
}

FileTapeLibrary::ArrayRecord::ArrayRecord(std::initializer_list<int> list) {
	data = std::vector<int>(list);
}

FileTapeLibrary::ArrayRecord::ArrayRecord(int* array, std::size_t size) {
	data = std::vector<int>(array, array + size);
}

std::size_t FileTapeLibrary::ArrayRecord::size() const {
	return this->data.size();
}

/*void FileTapeLibrary::ArrayRecord::resize(size_t size) {
	data.resize(size);
}*/

/*std::string FileTapeLibrary::ArrayRecord::serialize() {
	auto record_str = std::string();

	// append size to string
	record_str += std::to_string(size());

	// append data to string
	for (auto element : data) {
		record_str += ' ';
		record_str += std::to_string(element);
	}

	return record_str;
}

void FileTapeLibrary::ArrayRecord::deserialize(std::istream& is) {
	// read size
	std::size_t size;
	is >> size;

	// declare data block
	data = std::vector<int>(size);

	// read data
	for (std::size_t i = 0; i < size; ++i) {
		is >> data[i];
	}
}*/

// bool FileTapeLibrary::ArrayRecord::operator<(const ArrayRecord& other) const {
//     return this->max() < other.max();
// }
//
// bool FileTapeLibrary::ArrayRecord::operator<=(const ArrayRecord& other) const {
// 	return this->max() <= other.max();
// }
//
// bool FileTapeLibrary::ArrayRecord::operator>(const ArrayRecord& other) const {
// 	return this->max() > other.max();
// }
//
// bool FileTapeLibrary::ArrayRecord::operator>=(const ArrayRecord& other) const {
// 	return this->max() >= other.max();
// }
//
// bool FileTapeLibrary::ArrayRecord::operator==(const ArrayRecord& other) const {
// 	return this->max() >= other.max();
// }
//
// bool FileTapeLibrary::ArrayRecord::operator!=(const ArrayRecord& other) const {
// 	return this->max() >= other.max();
// }

int FileTapeLibrary::ArrayRecord::max() const {
	if (size() <= 0) {
		throw std::exception("record has no data");
	}
	int max = data[0];
	
	for (int i = 1; i < size(); ++i) {
		if (data[i] > max) {
			max = data[i];
		}
	}

	return max;
}

bool FileTapeLibrary::ArrayRecord::is_valid() const {
	return size() > 0;
}

std::string FileTapeLibrary::ArrayRecord::short_format() const {
	if (is_valid()) {
		return std::to_string(max());
	}
	return "DNE";
}

namespace FileTapeLibrary {
	std::ostream& operator<<(std::ostream& os, const FileTapeLibrary::ArrayRecord& ar) {
		os << ar.short_format();
		return os;
		
		// if record is not valid
		if (!ar.is_valid()) {
			os << "DNE";
			return os;
		}

		// output size
		os << "{ ";

		//write data
		for (auto& element : ar.data) {
			os << element;
			if (&element != &ar.data.back()) {
				os << ", ";
			}
		}

		os << " }";
		return os;
	}
}
