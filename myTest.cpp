#include <memory>
#include <vector>
#include <string>

int main ()
{
	std::vector<std::string> a;	
	a.get_allocator().address();
}