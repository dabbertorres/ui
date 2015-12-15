#ifndef UI_THEME_HPP
#define UI_THEME_HPP

#include <unordered_map>
#include <string>

namespace ui
{
	class Theme
	{
		public:
			// map of elements to properties to values
			using Properties = std::unordered_map<std::string, std::string>;
			using Elements = std::unordered_map<std::string, Properties>;
			
			Theme();
			~Theme();

			void load(std::istream& istream);

			void add(const std::string& elem, const std::string& prop, const std::string& val);

			const Properties& get(const std::string& elem) const;
			const std::string& get(const std::string& elem, const std::string& prop) const;

		private:
			Elements properties;
	};
}

#endif
