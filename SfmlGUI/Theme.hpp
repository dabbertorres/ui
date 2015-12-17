#ifndef UI_THEME_HPP
#define UI_THEME_HPP

#include <unordered_map>
#include <string>

namespace ui
{
	class Theme
	{
		public:
			struct Property
			{
				public:
					Property() = default;
					Property(const std::string& str);
					Property(std::string&& str);

					operator bool() const;
					operator int() const;
					operator float() const;
					operator std::string() const;

				private:
					std::string value;
			};

			// map of elements to properties to values
			using Properties = std::unordered_map<std::string, Property>;
			using Elements = std::unordered_map<std::string, Properties>;
			
			Theme();
			~Theme();

			void load(std::istream& istream);

			void add(const std::string& elem, const std::string& prop, const std::string& val);

			const Properties& get(const std::string& elem) const;
			const Property& get(const std::string& elem, const std::string& prop) const;

			Elements::const_iterator begin() const;
			Elements::const_iterator end() const;

		private:
			Elements properties;
	};
}

#endif
