#ifndef UI_CONTAINER_HPP
#define UI_CONTAINER_HPP

#include "Control.hpp"

#include <vector>

namespace dbr
{
	namespace ui
	{
		class Container : public Control
		{
			public:
				Container();
				virtual ~Container();

			private:
				std::vector<Control*> children;
		};
	}
}

#endif
