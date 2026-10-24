#include "bitum/Meta.h"

#include <stdio.h>

class test : public bitum::meta::IMetaclass {
    BitumProperty(int, m_test);

    public:
        test() {
            m_test = 25;
            printf("V = %d\n", m_test + 5);
        }
};

int main(int argc, char** argv) {
    test meta_test;

    return 0;
}
