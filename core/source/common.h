#pragma once

#include <memory>
#include <optional>
#include <chrono>
#include <string>
#include <string_view>
#include <sstream>
#include <array>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include <fstream>
#include <stack>
#include <algorithm>
#include <cassert>
#include <functional>
#include <thread>
#include <mutex>
#include <future>
#include <limits>
#include <cctype>
#include <stdio.h>
#include <stdarg.h>

#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/wrap.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif