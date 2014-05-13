#include "ComputerPlayerUtils.h"

namespace engine {

	Players ComputerPlayerUtils::InvertPlayer(Players player) {
		if (player == Players::Min) {
			return Players::Max;
		}
		return Players::Min;
	}
}
