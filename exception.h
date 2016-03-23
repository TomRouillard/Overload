#include <exception>
#include <string>

namespace exception
{
	class EmptyDirectory : public std::exception
	{
	public:
		EmptyDirectory(std::string directory)
		{
			_directory = directory;
		}

		virtual const char* what() const throw()
		{
			return ("Trying to reach a file in " + _directory + " but it is empty.").c_str();
		}
		
	private:
		std::string _directory;
	};
}