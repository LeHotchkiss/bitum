#include "bitum/Meta.h"
#include "bitum/Math.h"
#include "hlib/Print.h"

#include <stdio.h>

class test : public bitum::meta::IMetaclass {
    BitumProperty(int, m_test);

    public:
        test() {
            m_test = 25;
            m_test = m_test / 5;
            printf("V = %d\n", (int)m_test);
        }
};

int main(int argc, char** argv) {
    test meta_test;

    hlib::Print(hlib::OutStream, "Max = ", bitum::math::Max(-1000, 1, 500, 0, 52), "\n");
    hlib::Print(hlib::OutStream, "Min = ", bitum::math::Min(-1000, 1, 500, 0, 52), "\n");

    return 0;
}
