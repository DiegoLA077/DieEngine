#include <gtest/gtest.h>
#include <DieAplicationBase.h>

//TEST(DiegoLA, Test1) {
//  ASSERT_TRUE(1 == 1);
//}

namespace dieEngineSDK {
  class Size_Test : public DieAplicationBase
  {
   public:
    Size_Test() {
      m_iScrWidth = 900;
      m_iScrHeight = 800;
      m_szTitle = "DieEngine";
    }
  };
}

dieEngineSDK::Size_Test g_App;

int
main() {

  return g_App.run();
}