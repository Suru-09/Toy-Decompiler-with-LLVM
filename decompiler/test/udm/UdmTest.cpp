#include "gtest/gtest.h"

#include "udm/UDM.h"

#include <iostream>
#include <memory>

class UdmTest : public ::testing::Test
{
    void setUp()
    {

    }

    void tearDown()
    {

    }
private:
    std::shared_ptr<udm::UDM> udm;
};

TEST_F(UdmTest, testTrue)
{
    assert(true);
}


