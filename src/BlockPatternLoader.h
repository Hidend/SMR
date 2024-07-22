#include "BlockPattern.h"
#include <vector>
#include <string>

class BlockPatternLoader {
public:
    static std::vector<BlockPattern> loadBlockPatterns(const std::string& filename);
};