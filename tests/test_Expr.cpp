//
//
//  test_Expr.cpp
//  compiler-workout-llvm
//
//  Created by Sergej Jaskiewicz on 22/02/2019
//
//  GitHub
//  https://github.com/broadwaylamb/compiler-workout-llvm
//

#include "Expr.h"

#include <cassert>

using namespace compiler_workout;

// MARK: - Test helpers

namespace {

template <typename T> struct unique_ptr {

  template <typename U>
  unique_ptr(std::unique_ptr<U> ptr) : wrapped_(std::move(ptr)) {}

  T& operator*() { return *wrapped_; }

  const std::unique_ptr<T>& operator->() { return wrapped_; }

  std::unique_ptr<T> take() { return std::move(wrapped_); }

private:
  std::unique_ptr<T> wrapped_;
};

unique_ptr<Expr> let(int value) {
  return std::make_unique<ConstExpr>(value);
}

unique_ptr<Expr> var(const char* name) {
  return std::make_unique<VarExpr>(name);
}

unique_ptr<Expr> operator+(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("+", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator-(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("-", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator*(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("*", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator<(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("<", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator<=(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("<=", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator>(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>(">", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator>=(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>(">=", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator==(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("==", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator!=(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("!=", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator&&(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("&&", lhs.take(), rhs.take());
}

unique_ptr<Expr> operator||(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) {
  return std::make_unique<BinopExpr>("!!", lhs.take(), rhs.take());
}

} // namespace

// MARK: - Tests

int main() {

  {
    State state = {{"x0", 772}, {"x1", 270}, {"x2", 779}};
    auto expr   = (((((var("x2")) + (let(264))) * ((var("x0")) * (var("x2")))) -
                  (((var("x2")) - (var("x0"))) + ((let(58)) + (var("x1"))))));
    auto result = expr->eval(state);
    assert(result && *result == 627247349);
  }

  {
    State state = {{"x0", 152}, {"x1", 735}, {"x2", 825}};
    auto expr   = (((((let(20)) + (var("x2"))) - ((let(442)) * (var("x1")))) +
                  (((var("x2")) - (var("x1"))) * ((let(799)) + (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == -177865);
  }

  {
    State state = {{"x0", 233}, {"x1", 682}, {"x2", 165}};
    auto expr   = (((((let(403)) + (let(641))) + ((let(197)) + (let(788)))) -
                  (((var("x0")) - (var("x2"))) - ((var("x0")) * (let(91))))));
    auto result = expr->eval(state);
    assert(result && *result == 23164);
  }

  {
    State state = {{"x0", 380}, {"x1", 120}, {"x2", 283}};
    auto expr   = (((((let(763)) * (var("x1"))) + ((var("x2")) * (var("x0")))) *
                  (((let(75)) + (let(231))) - ((var("x1")) * (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == -6700511400);
  }

  {
    State state = {{"x0", 351}, {"x1", 786}, {"x2", 52}};
    auto expr   = (((((let(312)) * (var("x1"))) * ((let(944)) * (var("x1")))) +
                  (((var("x0")) + (var("x2"))) * ((var("x2")) * (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == 181959310000);
  }

  {
    State state = {{"x0", 829}, {"x1", 146}, {"x2", 601}};
    auto expr   = (((((var("x1")) + (var("x2"))) + ((let(264)) * (let(312)))) +
                  (((var("x1")) + (let(91))) * ((var("x0")) + (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == 422025);
  }

  {
    State state = {{"x0", 288}, {"x1", 299}, {"x2", 455}};
    auto expr   = (((((let(797)) - (var("x2"))) + ((let(473)) + (let(970)))) -
                  (((let(348)) - (let(995))) + ((var("x2")) - (let(406))))));
    auto result = expr->eval(state);
    assert(result && *result == 2383);
  }

  {
    State state = {{"x0", 986}, {"x1", 185}, {"x2", 163}};
    auto expr   = (((((let(290)) - (let(865))) + ((let(289)) + (var("x1")))) +
                  (((let(34)) - (var("x2"))) + ((let(135)) + (let(651))))));
    auto result = expr->eval(state);
    assert(result && *result == 556);
  }

  {
    State state = {{"x0", 205}, {"x1", 352}, {"x2", 947}};
    auto expr   = (((((var("x2")) + (let(757))) + ((let(352)) + (let(957)))) -
                  (((let(126)) * (let(296))) - ((let(628)) + (let(759))))));
    auto result = expr->eval(state);
    assert(result && *result == -32896);
  }

  {
    State state = {{"x0", 405}, {"x1", 434}, {"x2", 999}};
    auto expr   = (((((let(195)) + (var("x0"))) * ((let(591)) + (var("x1")))) -
                  (((var("x0")) + (var("x0"))) * ((let(164)) + (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == -327030);
  }

  {
    State state = {{"x0", 697}, {"x1", 245}, {"x2", 438}, {"x3", 652}};
    auto expr   = (((((var("x3")) * (var("x0"))) - ((var("x3")) * (let(0)))) +
                  (((let(202)) * (let(126))) - ((var("x0")) - (var("x1"))))));
    auto result = expr->eval(state);
    assert(result && *result == 479444);
  }

  {
    State state = {{"x0", 296}, {"x1", 843}, {"x2", 403}, {"x3", 629}};
    auto expr   = (((((var("x3")) * (var("x3"))) + ((let(628)) + (let(920)))) *
                  (((var("x0")) * (var("x3"))) + ((var("x2")) * (let(915))))));
    auto result = expr->eval(state);
    assert(result && *result == 220411694581);
  }

  {
    State state = {{"x0", 102}, {"x1", 232}, {"x2", 130}, {"x3", 226}};
    auto expr   = (((((var("x3")) + (let(662))) - ((var("x2")) + (let(329)))) +
                  (((let(68)) - (let(606))) + ((let(73)) * (let(734))))));
    auto result = expr->eval(state);
    assert(result && *result == 53473);
  }

  {
    State state = {{"x0", 855}, {"x1", 4}, {"x2", 569}, {"x3", 49}};
    auto expr   = (((((var("x3")) + (let(901))) - ((let(8)) - (let(345)))) *
                  (((let(639)) * (let(420))) - ((let(236)) * (var("x0"))))));
    auto result = expr->eval(state);
    assert(result && *result == 85714200);
  }

  {
    State state = {{"x0", 477}, {"x1", 362}, {"x2", 724}, {"x3", 801}};
    auto expr   = (((((var("x0")) * (var("x2"))) + ((let(776)) + (let(182)))) +
                  (((let(801)) - (var("x1"))) * ((var("x1")) * (let(490))))));
    auto result = expr->eval(state);
    assert(result && *result == 78216126);
  }

  {
    State state = {{"x0", 688}, {"x1", 113}, {"x2", 498}, {"x3", 881}};
    auto expr   = (((((var("x2")) + (let(566))) + ((var("x0")) + (var("x2")))) +
                  (((var("x2")) + (let(576))) - ((let(271)) + (var("x1"))))));
    auto result = expr->eval(state);
    assert(result && *result == 2940);
  }

  {
    State state = {{"x0", 450}, {"x1", 106}, {"x2", 801}, {"x3", 428}};
    auto expr   = (((((var("x1")) - (var("x0"))) * ((let(126)) * (var("x3")))) -
                  (((let(761)) * (var("x0"))) * ((let(539)) * (let(281))))));
    auto result = expr->eval(state);
    assert(result && *result == -51885685782);
  }

  {
    State state = {{"x0", 230}, {"x1", 92}, {"x2", 397}, {"x3", 149}};
    auto expr   = (((((var("x2")) + (var("x3"))) * ((var("x1")) - (let(745)))) +
                  (((var("x0")) + (var("x3"))) - ((let(335)) + (let(449))))));
    auto result = expr->eval(state);
    assert(result && *result == -356943);
  }

  {
    State state = {{"x0", 674}, {"x1", 642}, {"x2", 658}, {"x3", 658}};
    auto expr   = (((((var("x1")) * (var("x3"))) * ((let(322)) + (let(83)))) -
                  (((var("x0")) + (var("x1"))) * ((var("x3")) * (var("x1"))))));
    auto result = expr->eval(state);
    assert(result && *result == -384839196);
  }

  {
    State state = {{"x0", 260}, {"x1", 447}, {"x2", 700}, {"x3", 613}};
    auto expr   = (((((let(633)) - (var("x2"))) * ((var("x2")) + (var("x0")))) *
                  (((let(475)) - (var("x1"))) - ((let(561)) * (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == 25256663040);
  }

  {
    State state = {
        {"x0", 633}, {"x1", 613}, {"x2", 433}, {"x3", 288}, {"x4", 857}};
    auto expr = ((((((let(165)) + (var("x0"))) * ((var("x4")) * (var("x2")))) -
                   (((var("x4")) + (let(613))) - ((let(471)) * (let(656))))) *
                  ((((var("x2")) - (var("x0"))) + ((let(303)) - (let(449)))) -
                   (((let(385)) + (var("x0"))) + ((let(782)) + (var("x2")))))));
    auto result = expr->eval(state);
    assert(result && *result == -764493341376);
  }

  {
    State state = {
        {"x0", 947}, {"x1", 730}, {"x2", 835}, {"x3", 646}, {"x4", 995}};
    auto expr =
        ((((((let(335)) * (var("x0"))) * ((let(841)) - (let(650)))) *
           (((let(827)) - (let(748))) * ((let(437)) * (let(503))))) -
          ((((var("x0")) + (let(519))) * ((var("x3")) * (let(285)))) -
           (((var("x0")) + (let(207))) + ((var("x0")) + (var("x3")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1052215161244342);
  }

  {
    State state = {
        {"x0", 203}, {"x1", 521}, {"x2", 582}, {"x3", 13}, {"x4", 729}};
    auto expr = ((((((var("x4")) + (var("x2"))) - ((var("x1")) + (var("x4")))) -
                   (((let(257)) * (let(959))) * ((var("x4")) - (var("x4"))))) *
                  ((((var("x2")) * (var("x2"))) - ((var("x2")) + (var("x0")))) *
                   (((let(877)) - (let(509))) + ((let(419)) - (var("x1")))))));
    auto result = expr->eval(state);
    assert(result && *result == 5483398214);
  }

  {
    State state = {
        {"x0", 20}, {"x1", 382}, {"x2", 143}, {"x3", 4}, {"x4", 709}};
    auto expr   = ((((((var("x4")) + (let(958))) - ((let(739)) - (var("x2")))) -
                   (((var("x1")) + (var("x1"))) + ((var("x1")) * (let(737))))) *
                  ((((var("x4")) - (let(946))) + ((let(212)) * (let(645)))) *
                   (((var("x4")) - (let(660))) + ((var("x0")) * (let(514)))))));
    auto result = expr->eval(state);
    assert(result && *result == -396513052110549);
  }

  {
    State state = {
        {"x0", 991}, {"x1", 50}, {"x2", 719}, {"x3", 911}, {"x4", 24}};
    auto expr   = ((((((let(624)) * (var("x0"))) * ((let(113)) - (let(320)))) -
                   (((let(270)) * (var("x4"))) + ((let(390)) + (let(814))))) -
                  ((((var("x1")) - (var("x4"))) - ((var("x0")) + (var("x3")))) +
                   (((let(633)) - (var("x4"))) * ((let(501)) - (var("x2")))))));
    auto result = expr->eval(state);
    assert(result && *result == -127878534);
  }

  {
    State state = {
        {"x0", 535}, {"x1", 435}, {"x2", 714}, {"x3", 581}, {"x4", 354}};
    auto expr   = ((((((var("x0")) * (let(370))) + ((let(24)) - (var("x1")))) +
                   (((let(120)) * (let(219))) + ((var("x3")) - (let(986))))) +
                  ((((var("x0")) + (let(87))) + ((var("x0")) + (var("x0")))) *
                   (((var("x3")) - (let(301))) - ((let(567)) + (let(209)))))));
    auto result = expr->eval(state);
    assert(result && *result == -615818);
  }

  {
    State state = {
        {"x0", 426}, {"x1", 446}, {"x2", 160}, {"x3", 458}, {"x4", 160}};
    auto expr = ((((((let(816)) * (var("x4"))) - ((var("x0")) + (var("x0")))) +
                   (((var("x0")) + (let(807))) - ((var("x4")) - (var("x1"))))) *
                  ((((let(640)) + (let(266))) - ((let(768)) * (let(810)))) *
                   (((let(390)) + (let(559))) * ((let(724)) - (let(76)))))));
    auto result = expr->eval(state);
    assert(result && *result == -50127689595846096);
  }

  {
    State state = {
        {"x0", 938}, {"x1", 524}, {"x2", 256}, {"x3", 582}, {"x4", 967}};
    auto expr   = ((((((let(879)) * (let(234))) * ((var("x4")) * (let(59)))) -
                   (((let(770)) - (var("x1"))) + ((var("x0")) + (let(973))))) +
                  ((((let(254)) + (let(726))) * ((let(542)) - (var("x1")))) *
                   (((let(228)) * (var("x2"))) + ((var("x0")) * (let(502)))))));
    auto result = expr->eval(state);
    assert(result && *result == 21070865361);
  }

  {
    State state = {
        {"x0", 109}, {"x1", 795}, {"x2", 155}, {"x3", 658}, {"x4", 30}};
    auto expr   = ((((((let(422)) + (let(379))) + ((let(211)) + (var("x0")))) -
                   (((let(206)) + (var("x3"))) + ((var("x3")) - (var("x3"))))) +
                  ((((let(895)) + (let(411))) * ((var("x4")) - (var("x2")))) *
                   (((var("x1")) - (let(628))) + ((var("x0")) * (let(403)))))));
    auto result = expr->eval(state);
    assert(result && *result == -7198345243);
  }

  {
    State state = {
        {"x0", 795}, {"x1", 262}, {"x2", 666}, {"x3", 694}, {"x4", 943}};
    auto expr   = ((((((var("x4")) - (let(177))) - ((var("x3")) - (let(886)))) *
                   (((let(836)) * (var("x4"))) + ((let(289)) * (var("x3"))))) +
                  ((((let(260)) + (var("x0"))) - ((var("x4")) - (var("x3")))) +
                   (((let(460)) * (let(450))) + ((var("x2")) + (var("x1")))))));
    auto result = expr->eval(state);
    assert(result && *result == 947588346);
  }

  {
    State state = {{"x0", 509},
                   {"x1", 876},
                   {"x2", 280},
                   {"x3", 393},
                   {"x4", 446},
                   {"x5", 128}};
    auto expr =
        ((((((let(855)) + (var("x4"))) + ((let(215)) + (var("x0")))) +
           (((let(481)) - (let(776))) - ((var("x4")) - (var("x4"))))) -
          ((((let(712)) + (let(485))) + ((let(971)) * (let(781)))) +
           (((var("x2")) * (var("x3"))) * ((var("x5")) - (let(996)))))));
    auto result = expr->eval(state);
    assert(result && *result == 94756902);
  }

  {
    State state = {{"x0", 561},
                   {"x1", 549},
                   {"x2", 417},
                   {"x3", 639},
                   {"x4", 507},
                   {"x5", 439}};
    auto expr =
        ((((((var("x1")) * (let(291))) - ((var("x5")) - (let(858)))) -
           (((var("x2")) * (var("x4"))) + ((let(827)) * (var("x1"))))) -
          ((((var("x3")) - (var("x3"))) - ((let(599)) * (var("x4")))) -
           (((var("x5")) - (let(886))) - ((var("x4")) * (var("x3")))))));
    auto result = expr->eval(state);
    assert(result && *result == -525991);
  }

  {
    State state = {{"x0", 695},
                   {"x1", 148},
                   {"x2", 358},
                   {"x3", 175},
                   {"x4", 75},
                   {"x5", 193}};
    auto expr =
        ((((((let(331)) - (let(292))) + ((var("x1")) * (var("x5")))) -
           (((let(310)) * (let(304))) * ((var("x4")) - (var("x4"))))) +
          ((((var("x5")) + (var("x2"))) * ((var("x0")) + (let(732)))) -
           (((let(396)) * (var("x5"))) * ((var("x3")) * (var("x4")))))));
    auto result = expr->eval(state);
    assert(result && *result == -1002302620);
  }

  {
    State state = {{"x0", 858},
                   {"x1", 997},
                   {"x2", 883},
                   {"x3", 987},
                   {"x4", 121},
                   {"x5", 53}};
    auto expr =
        ((((((let(725)) * (let(587))) + ((let(144)) * (let(91)))) *
           (((var("x5")) + (let(590))) + ((var("x5")) * (let(618))))) *
          ((((var("x4")) - (var("x2"))) + ((var("x4")) + (var("x4")))) -
           (((let(931)) - (var("x4"))) - ((var("x1")) * (var("x4")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1747914667703841);
  }

  {
    State state = {{"x0", 988},
                   {"x1", 748},
                   {"x2", 167},
                   {"x3", 781},
                   {"x4", 981},
                   {"x5", 769}};
    auto expr   = ((((((var("x4")) * (var("x3"))) - ((let(83)) * (let(619)))) +
                   (((let(726)) - (var("x5"))) * ((var("x1")) + (let(38))))) -
                  ((((let(91)) * (var("x0"))) + ((let(0)) + (var("x4")))) *
                   (((let(949)) - (let(511))) * ((var("x5")) * (let(714)))))));
    auto result = expr->eval(state);
    assert(result && *result == -21857977456226);
  }

  {
    State state = {{"x0", 647},
                   {"x1", 166},
                   {"x2", 61},
                   {"x3", 125},
                   {"x4", 256},
                   {"x5", 171}};
    auto expr   = ((((((let(598)) - (let(288))) - ((let(23)) * (var("x0")))) +
                   (((var("x3")) - (var("x1"))) - ((var("x1")) * (let(906))))) *
                  ((((let(895)) * (var("x2"))) * ((var("x4")) - (var("x1")))) *
                   (((let(179)) - (var("x1"))) * ((var("x5")) + (let(470)))))));
    auto result = expr->eval(state);
    assert(result && *result == -6756188561647200);
  }

  {
    State state = {{"x0", 190},
                   {"x1", 823},
                   {"x2", 226},
                   {"x3", 530},
                   {"x4", 417},
                   {"x5", 536}};
    auto expr   = ((((((let(633)) + (let(989))) + ((var("x3")) * (let(957)))) -
                   (((var("x5")) * (var("x1"))) - ((let(872)) - (let(998))))) +
                  ((((var("x3")) * (let(644))) - ((var("x1")) * (let(182)))) +
                   (((let(387)) + (let(662))) - ((let(321)) - (var("x0")))))));
    auto result = expr->eval(state);
    assert(result && *result == 260030);
  }

  {
    State state = {{"x0", 351},
                   {"x1", 771},
                   {"x2", 843},
                   {"x3", 415},
                   {"x4", 762},
                   {"x5", 986}};
    auto expr   = ((((((let(72)) + (var("x2"))) - ((let(830)) * (let(335)))) +
                   (((var("x1")) - (let(634))) + ((let(550)) * (let(660))))) +
                  ((((let(960)) * (let(482))) - ((var("x3")) - (var("x2")))) -
                   (((var("x1")) * (var("x3"))) + ((let(704)) * (let(869)))))));
    auto result = expr->eval(state);
    assert(result && *result == -382591);
  }

  {
    State state = {{"x0", 67},
                   {"x1", 188},
                   {"x2", 687},
                   {"x3", 888},
                   {"x4", 597},
                   {"x5", 185}};
    auto expr =
        ((((((let(914)) - (var("x5"))) + ((let(139)) * (var("x4")))) *
           (((var("x5")) * (var("x0"))) + ((let(262)) * (let(822))))) +
          ((((let(748)) - (var("x2"))) - ((var("x4")) * (var("x0")))) *
           (((var("x1")) + (var("x3"))) + ((let(392)) + (var("x0")))))));
    auto result = expr->eval(state);
    assert(result && *result == 19004856578);
  }

  {
    State state = {{"x0", 822},
                   {"x1", 27},
                   {"x2", 601},
                   {"x3", 277},
                   {"x4", 790},
                   {"x5", 163}};
    auto expr =
        ((((((var("x2")) - (let(326))) * ((var("x4")) - (var("x0")))) -
           (((var("x0")) - (var("x5"))) + ((let(749)) - (let(84))))) -
          ((((var("x2")) * (var("x2"))) + ((var("x5")) - (let(7)))) -
           (((var("x5")) - (var("x5"))) + ((let(295)) - (var("x0")))))));
    auto result = expr->eval(state);
    assert(result && *result == -372008);
  }

  {
    State state = {{"x0", 447},
                   {"x1", 286},
                   {"x2", 940},
                   {"x3", 522},
                   {"x4", 79},
                   {"x5", 750},
                   {"x6", 41}};
    auto expr =
        (((((((let(473)) - (var("x3"))) + ((let(542)) * (var("x3")))) -
            (((var("x6")) + (var("x6"))) * ((var("x3")) * (let(73))))) *
           ((((let(104)) + (let(675))) * ((var("x5")) * (let(984)))) +
            (((let(508)) + (let(372))) - ((var("x3")) * (let(665)))))) +
          (((((var("x0")) + (let(401))) - ((let(40)) - (var("x4")))) +
            (((let(755)) * (var("x4"))) - ((var("x4")) + (let(395))))) *
           ((((let(831)) * (var("x6"))) * ((let(423)) - (var("x4")))) *
            (((var("x4")) + (let(584))) + ((var("x1")) * (let(282))))))));
    auto result = expr->eval(state);
    assert(result && *result == 55605271039900730);
  }

  {
    State state = {{"x0", 221},
                   {"x1", 581},
                   {"x2", 872},
                   {"x3", 554},
                   {"x4", 448},
                   {"x5", 158},
                   {"x6", 566}};
    auto expr =
        (((((((var("x1")) * (var("x5"))) - ((var("x0")) - (var("x2")))) +
            (((var("x1")) - (let(136))) - ((var("x5")) * (var("x2"))))) -
           ((((let(991)) * (let(724))) * ((let(704)) - (let(685)))) -
            (((var("x3")) - (var("x1"))) + ((let(95)) - (let(88)))))) *
          (((((let(435)) + (let(822))) - ((let(917)) + (let(694)))) *
            (((let(659)) * (let(530))) - ((var("x3")) + (var("x3"))))) -
           ((((let(472)) + (let(689))) - ((let(401)) * (var("x6")))) -
            (((let(410)) - (var("x4"))) + ((let(118)) - (var("x6"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 1682611700987842);
  }

  {
    State state = {{"x0", 274},
                   {"x1", 152},
                   {"x2", 649},
                   {"x3", 245},
                   {"x4", 523},
                   {"x5", 580},
                   {"x6", 714}};
    auto expr =
        (((((((var("x2")) * (var("x2"))) - ((let(383)) * (var("x4")))) *
            (((let(642)) + (let(68))) + ((var("x4")) * (let(317))))) *
           ((((var("x6")) - (let(621))) * ((let(334)) + (var("x2")))) +
            (((let(181)) + (var("x5"))) - ((var("x0")) + (let(990)))))) -
          (((((var("x2")) + (var("x2"))) * ((var("x3")) - (var("x1")))) +
            (((let(624)) - (let(636))) + ((var("x5")) + (var("x5"))))) *
           ((((var("x5")) + (let(624))) * ((var("x0")) + (var("x4")))) *
            (((var("x1")) * (let(392))) - ((let(884)) + (let(656))))))));
    auto result = expr->eval(state);
    assert(result && *result == -3443733562308592);
  }

  {
    State state = {{"x0", 37},
                   {"x1", 905},
                   {"x2", 599},
                   {"x3", 116},
                   {"x4", 494},
                   {"x5", 253},
                   {"x6", 499}};
    auto expr =
        (((((((let(277)) * (let(741))) + ((let(722)) + (let(866)))) +
            (((var("x3")) + (var("x6"))) * ((let(844)) + (var("x6"))))) +
           ((((let(489)) - (var("x5"))) * ((var("x3")) * (let(488)))) *
            (((let(276)) + (var("x3"))) - ((let(198)) + (var("x2")))))) -
          (((((let(106)) + (var("x2"))) * ((var("x4")) + (var("x0")))) -
            (((var("x4")) - (let(151))) + ((var("x5")) - (let(763))))) -
           ((((var("x4")) * (let(501))) * ((var("x1")) - (let(653)))) *
            (((let(795)) + (var("x1"))) - ((var("x3")) - (let(722))))))));
    auto result = expr->eval(state);
    assert(result && *result == 138411798956);
  }

  {
    State state = {{"x0", 276},
                   {"x1", 354},
                   {"x2", 699},
                   {"x3", 367},
                   {"x4", 93},
                   {"x5", 559},
                   {"x6", 12},
                   {"x7", 14}};
    auto expr =
        (((((((var("x0")) - (var("x4"))) + ((var("x2")) - (var("x2")))) *
            (((let(983)) + (let(436))) - ((let(166)) - (var("x7"))))) +
           ((((let(238)) * (var("x2"))) + ((let(210)) - (var("x7")))) +
            (((let(201)) - (let(781))) + ((var("x2")) - (let(28)))))) *
          (((((let(866)) + (let(455))) + ((let(783)) * (var("x4")))) *
            (((let(977)) - (var("x4"))) * ((var("x6")) - (let(229))))) -
           ((((var("x2")) + (let(740))) * ((var("x4")) * (let(496)))) +
            (((var("x6")) - (let(42))) * ((let(719)) * (let(543))))))));
    auto result = expr->eval(state);
    assert(result && *result == -5689445018333020);
  }

  {
    State state = {{"x0", 476}, {"x1", 183}, {"x2", 881}};
    auto expr   = (((((var("x2")) + (let(869))) - ((var("x1")) > (let(308)))) +
                  (((var("x1")) || (var("x0"))) >= ((var("x0")) + (let(0))))));
    auto result = expr->eval(state);
    assert(result && *result == 1750);
  }

  {
    State state = {{"x0", 246}, {"x1", 317}, {"x2", 804}};
    auto expr =
        (((((var("x0")) - (let(523))) < ((let(723)) == (let(961)))) *
          (((var("x1")) != (var("x1"))) || ((let(130)) >= (let(627))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 211}, {"x1", 68}, {"x2", 317}};
    auto expr   = (((((var("x1")) > (var("x1"))) + ((var("x1")) - (let(88)))) +
                  (((let(535)) > (var("x0"))) < ((let(565)) >= (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == -20);
  }

  {
    State state = {{"x0", 523}, {"x1", 188}, {"x2", 920}};
    auto expr =
        (((((var("x1")) + (let(350))) || ((var("x1")) != (let(634)))) ==
          (((var("x2")) <= (let(860))) >= ((var("x0")) || (var("x1"))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 877}, {"x1", 434}, {"x2", 278}};
    auto expr   = (((((var("x1")) && (let(927))) < ((let(742)) < (let(390)))) >
                  (((let(2)) > (var("x1"))) * ((var("x2")) >= (let(879))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 745}, {"x1", 991}, {"x2", 725}};
    auto expr =
        (((((let(305)) >= (let(820))) >= ((let(9)) != (let(528)))) !=
          (((var("x2")) >= (let(727))) == ((var("x2")) && (var("x0"))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 586}, {"x1", 518}, {"x2", 454}};
    auto expr = (((((var("x2")) > (let(215))) == ((var("x2")) * (var("x0")))) <
                  (((var("x0")) - (let(809))) != ((let(993)) != (let(437))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 875}, {"x1", 938}, {"x2", 833}};
    auto expr   = (((((let(135)) > (var("x2"))) > ((let(925)) && (let(179)))) >=
                  (((var("x2")) || (let(396))) < ((var("x2")) >= (let(85))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 320}, {"x1", 764}, {"x2", 341}};
    auto expr = (((((var("x0")) > (var("x1"))) >= ((let(113)) * (let(551)))) &&
                  (((let(910)) < (let(324))) > ((let(814)) - (var("x2"))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 58}, {"x1", 176}, {"x2", 182}};
    auto expr = (((((var("x0")) + (let(955))) || ((var("x2")) || (var("x2")))) *
                  (((var("x1")) || (var("x0"))) > ((var("x2")) + (let(118))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 176}, {"x1", 207}, {"x2", 710}, {"x3", 873}};
    auto expr =
        (((((var("x3")) || (let(564))) || ((let(636)) + (let(543)))) !=
          (((var("x0")) != (var("x1"))) - ((var("x3")) && (var("x1"))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 383}, {"x1", 338}, {"x2", 176}, {"x3", 202}};
    auto expr = (((((let(543)) > (let(850))) * ((var("x2")) >= (var("x3")))) ||
                  (((let(459)) == (var("x2"))) != ((let(314)) > (let(77))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 277}, {"x1", 241}, {"x2", 91}, {"x3", 259}};
    auto expr   = (((((let(924)) && (let(260))) - ((let(54)) != (var("x0")))) ||
                  (((let(307)) || (var("x3"))) * ((let(94)) - (let(299))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 502}, {"x1", 31}, {"x2", 230}, {"x3", 288}};
    auto expr   = (((((let(298)) - (let(423))) || ((let(394)) < (let(502)))) !=
                  (((let(369)) != (let(462))) - ((var("x2")) <= (let(621))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 398}, {"x1", 208}, {"x2", 808}, {"x3", 564}};
    auto expr = (((((var("x0")) > (let(95))) && ((var("x1")) < (var("x3")))) ||
                  (((var("x2")) || (let(223))) || ((var("x2")) + (let(857))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 455}, {"x1", 633}, {"x2", 821}, {"x3", 915}};
    auto expr   = (((((let(54)) > (let(174))) || ((var("x1")) > (var("x1")))) >=
                  (((var("x2")) && (let(928))) >= ((let(612)) - (let(285))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 896}, {"x1", 770}, {"x2", 426}, {"x3", 754}};
    auto expr = (((((let(253)) <= (let(595))) <= ((var("x1")) < (var("x2")))) <
                  (((let(691)) < (let(573))) <= ((var("x0")) && (let(954))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 195}, {"x1", 544}, {"x2", 963}, {"x3", 311}};
    auto expr = (((((let(235)) <= (var("x2"))) + ((var("x1")) + (var("x3")))) ==
                  (((var("x3")) * (let(353))) < ((var("x2")) && (let(984))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 988}, {"x1", 974}, {"x2", 627}, {"x3", 543}};
    auto expr = (((((var("x3")) != (var("x3"))) - ((let(264)) && (var("x3")))) >
                  (((let(258)) || (let(710))) < ((let(743)) * (var("x3"))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 902}, {"x1", 175}, {"x2", 705}, {"x3", 154}};
    auto expr =
        (((((let(180)) && (var("x1"))) == ((var("x1")) || (var("x0")))) -
          (((let(552)) - (let(164))) && ((var("x1")) == (var("x1"))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {
        {"x0", 256}, {"x1", 359}, {"x2", 496}, {"x3", 200}, {"x4", 555}};
    auto expr =
        ((((((var("x0")) + (let(297))) == ((let(8)) - (var("x3")))) &&
           (((let(586)) > (let(22))) - ((let(84)) > (let(320))))) +
          ((((var("x4")) && (let(587))) * ((let(107)) - (let(233)))) ||
           (((var("x0")) > (var("x2"))) + ((var("x0")) - (let(445)))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {
        {"x0", 691}, {"x1", 557}, {"x2", 458}, {"x3", 321}, {"x4", 764}};
    auto expr =
        ((((((let(523)) < (var("x1"))) * ((let(416)) + (var("x3")))) ==
           (((let(685)) < (let(258))) && ((let(20)) == (var("x3"))))) ==
          ((((var("x1")) || (let(269))) != ((let(888)) > (let(485)))) >=
           (((var("x0")) - (var("x0"))) != ((var("x0")) || (let(771)))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {
        {"x0", 211}, {"x1", 212}, {"x2", 654}, {"x3", 107}, {"x4", 609}};
    auto expr =
        ((((((var("x0")) * (let(921))) == ((var("x2")) * (var("x2")))) >=
           (((var("x2")) && (var("x1"))) <= ((var("x4")) || (var("x2"))))) <=
          ((((let(971)) * (var("x3"))) != ((let(706)) <= (let(929)))) !=
           (((var("x2")) || (var("x3"))) > ((var("x4")) && (let(927)))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {
        {"x0", 439}, {"x1", 542}, {"x2", 740}, {"x3", 67}, {"x4", 3}};
    auto expr =
        ((((((let(679)) - (let(175))) < ((var("x4")) >= (let(987)))) ==
           (((let(902)) != (let(729))) || ((let(685)) - (var("x3"))))) <=
          ((((var("x0")) <= (var("x4"))) && ((var("x4")) - (var("x0")))) >=
           (((var("x1")) <= (var("x1"))) != ((var("x2")) * (var("x0")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {
        {"x0", 870}, {"x1", 274}, {"x2", 796}, {"x3", 95}, {"x4", 619}};
    auto expr =
        ((((((var("x2")) > (let(68))) > ((let(979)) > (var("x4")))) !=
           (((var("x4")) <= (var("x2"))) && ((var("x0")) >= (var("x0"))))) +
          ((((let(262)) + (var("x3"))) > ((var("x2")) > (var("x2")))) +
           (((let(394)) > (var("x2"))) == ((let(697)) == (let(844)))))));
    auto result = expr->eval(state);
    assert(result && *result == 3);
  }

  {
    State state = {
        {"x0", 531}, {"x1", 961}, {"x2", 937}, {"x3", 779}, {"x4", 337}};
    auto expr =
        ((((((var("x2")) < (var("x1"))) == ((var("x0")) - (var("x3")))) &&
           (((let(53)) <= (let(565))) * ((let(601)) <= (let(585))))) !=
          ((((var("x2")) != (var("x4"))) >= ((var("x3")) != (let(182)))) !=
           (((var("x1")) >= (let(386))) < ((let(214)) && (let(140)))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {
        {"x0", 203}, {"x1", 762}, {"x2", 156}, {"x3", 910}, {"x4", 837}};
    auto expr =
        ((((((var("x2")) >= (let(156))) - ((let(752)) && (let(401)))) !=
           (((var("x0")) <= (let(704))) - ((var("x3")) && (let(444))))) !=
          ((((var("x3")) != (let(677))) != ((var("x0")) * (var("x0")))) ||
           (((var("x3")) * (let(326))) && ((let(890)) >= (var("x0")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {
        {"x0", 56}, {"x1", 979}, {"x2", 696}, {"x3", 362}, {"x4", 380}};
    auto expr =
        ((((((var("x1")) <= (var("x0"))) >= ((let(174)) == (let(843)))) >
           (((let(206)) < (let(659))) != ((let(406)) < (var("x3"))))) ==
          ((((let(470)) - (let(978))) > ((let(228)) == (let(155)))) &&
           (((let(949)) != (let(856))) && ((let(720)) != (let(743)))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {
        {"x0", 731}, {"x1", 585}, {"x2", 666}, {"x3", 661}, {"x4", 746}};
    auto expr =
        ((((((let(144)) >= (var("x3"))) != ((var("x2")) >= (let(668)))) ==
           (((let(849)) == (let(624))) < ((let(405)) >= (var("x4"))))) *
          ((((var("x4")) - (var("x0"))) >= ((let(578)) <= (var("x2")))) -
           (((var("x2")) != (var("x3"))) - ((let(190)) > (var("x1")))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {
        {"x0", 259}, {"x1", 264}, {"x2", 997}, {"x3", 905}, {"x4", 0}};
    auto expr =
        ((((((let(381)) != (var("x1"))) < ((var("x3")) || (var("x2")))) <=
           (((var("x4")) || (var("x4"))) && ((var("x4")) + (var("x1"))))) <
          ((((let(186)) <= (var("x3"))) >= ((var("x4")) == (let(931)))) -
           (((var("x1")) + (let(185))) && ((var("x4")) < (let(986)))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 197},
                   {"x1", 986},
                   {"x2", 414},
                   {"x3", 476},
                   {"x4", 175},
                   {"x5", 468}};
    auto expr =
        ((((((var("x3")) && (var("x0"))) != ((var("x3")) + (let(79)))) *
           (((let(849)) < (let(679))) >= ((var("x2")) * (let(906))))) -
          ((((let(103)) - (var("x1"))) >= ((var("x3")) < (let(78)))) *
           (((let(108)) > (var("x2"))) + ((let(159)) <= (var("x3")))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 315},
                   {"x1", 607},
                   {"x2", 122},
                   {"x3", 908},
                   {"x4", 139},
                   {"x5", 6}};
    auto expr =
        ((((((var("x4")) + (let(697))) || ((let(914)) >= (let(381)))) +
           (((let(436)) && (var("x4"))) && ((let(671)) && (let(812))))) <
          ((((var("x1")) == (let(755))) > ((var("x2")) && (var("x1")))) *
           (((var("x2")) < (let(785))) < ((var("x5")) >= (var("x5")))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 729},
                   {"x1", 885},
                   {"x2", 916},
                   {"x3", 878},
                   {"x4", 575},
                   {"x5", 548}};
    auto expr =
        ((((((let(75)) - (let(299))) > ((let(445)) < (var("x2")))) <
           (((var("x4")) <= (let(286))) - ((let(687)) <= (var("x4"))))) +
          ((((let(689)) - (var("x5"))) + ((let(135)) && (var("x3")))) ||
           (((var("x5")) && (let(49))) != ((var("x5")) <= (var("x5")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 738},
                   {"x1", 296},
                   {"x2", 757},
                   {"x3", 384},
                   {"x4", 263},
                   {"x5", 443}};
    auto expr =
        ((((((let(484)) - (let(934))) != ((var("x1")) >= (var("x3")))) -
           (((var("x2")) == (let(77))) - ((let(563)) - (var("x4"))))) &&
          ((((var("x5")) && (var("x1"))) + ((var("x4")) == (var("x3")))) ==
           (((var("x0")) && (let(217))) - ((var("x4")) && (var("x2")))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 217},
                   {"x1", 279},
                   {"x2", 695},
                   {"x3", 451},
                   {"x4", 530},
                   {"x5", 71}};
    auto expr =
        ((((((let(48)) - (let(772))) + ((var("x5")) * (var("x5")))) ||
           (((var("x5")) * (var("x2"))) <= ((let(503)) - (let(354))))) ||
          ((((let(205)) < (let(120))) * ((var("x0")) > (var("x1")))) *
           (((var("x1")) < (var("x5"))) >= ((var("x2")) < (let(553)))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 328},
                   {"x1", 983},
                   {"x2", 663},
                   {"x3", 225},
                   {"x4", 490},
                   {"x5", 796}};
    auto expr =
        ((((((let(955)) != (var("x5"))) && ((var("x4")) && (let(716)))) -
           (((let(10)) > (let(852))) != ((let(563)) > (var("x1"))))) !=
          ((((let(145)) < (let(346))) * ((var("x1")) || (let(127)))) +
           (((var("x2")) != (let(676))) <= ((var("x5")) <= (var("x5")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 809},
                   {"x1", 472},
                   {"x2", 254},
                   {"x3", 342},
                   {"x4", 715},
                   {"x5", 694}};
    auto expr =
        ((((((var("x0")) + (var("x2"))) - ((var("x3")) - (var("x4")))) ==
           (((var("x4")) - (let(314))) > ((let(543)) < (let(641))))) *
          ((((var("x2")) < (var("x4"))) >= ((let(529)) != (var("x2")))) ||
           (((let(976)) - (var("x5"))) && ((var("x5")) != (var("x2")))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 373},
                   {"x1", 529},
                   {"x2", 334},
                   {"x3", 911},
                   {"x4", 728},
                   {"x5", 20}};
    auto expr =
        ((((((let(684)) == (var("x2"))) == ((let(381)) <= (var("x1")))) >=
           (((var("x5")) * (let(952))) < ((var("x3")) == (var("x5"))))) <=
          ((((var("x5")) > (let(171))) < ((var("x2")) * (var("x4")))) ||
           (((var("x1")) < (let(289))) || ((var("x4")) * (var("x4")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 746},
                   {"x1", 766},
                   {"x2", 343},
                   {"x3", 871},
                   {"x4", 53},
                   {"x5", 8}};
    auto expr =
        ((((((var("x4")) && (let(531))) <= ((var("x2")) * (var("x3")))) *
           (((var("x3")) > (let(963))) || ((let(563)) && (var("x5"))))) -
          ((((var("x5")) < (let(699))) + ((let(851)) - (let(162)))) +
           (((let(328)) <= (let(920))) || ((var("x3")) >= (let(68)))))));
    auto result = expr->eval(state);
    assert(result && *result == -690);
  }

  {
    State state = {{"x0", 639},
                   {"x1", 876},
                   {"x2", 27},
                   {"x3", 192},
                   {"x4", 138},
                   {"x5", 845}};
    auto expr =
        ((((((let(686)) + (var("x1"))) == ((var("x1")) >= (let(31)))) !=
           (((var("x0")) > (var("x3"))) >= ((var("x2")) < (var("x2"))))) ||
          ((((let(332)) < (let(463))) + ((let(548)) <= (var("x0")))) ||
           (((let(69)) >= (var("x0"))) > ((var("x0")) <= (var("x0")))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 207},
                   {"x1", 410},
                   {"x2", 839},
                   {"x3", 488},
                   {"x4", 566},
                   {"x5", 236},
                   {"x6", 761}};
    auto expr =
        (((((((let(863)) != (var("x1"))) && ((var("x2")) || (var("x1")))) !=
            (((var("x5")) <= (let(848))) + ((let(979)) || (let(106))))) !=
           ((((var("x6")) <= (let(419))) <= ((var("x6")) != (var("x3")))) <
            (((var("x3")) == (let(117))) == ((var("x5")) > (let(850)))))) <=
          (((((let(645)) + (let(539))) > ((let(49)) != (let(741)))) >=
            (((var("x1")) + (var("x5"))) || ((var("x3")) > (let(601))))) -
           ((((var("x5")) || (let(151))) && ((let(35)) - (let(866)))) *
            (((let(231)) || (let(335))) >= ((let(492)) == (let(477))))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 996},
                   {"x1", 790},
                   {"x2", 756},
                   {"x3", 593},
                   {"x4", 127},
                   {"x5", 158},
                   {"x6", 983}};
    auto expr =
        (((((((var("x3")) >= (let(756))) && ((let(991)) != (let(526)))) >
            (((let(92)) || (let(297))) * ((var("x2")) <= (var("x6"))))) <=
           ((((var("x0")) <= (var("x1"))) > ((let(147)) - (let(983)))) <
            (((var("x4")) && (let(980))) < ((let(842)) && (var("x1")))))) >=
          (((((var("x5")) + (var("x5"))) >= ((let(697)) <= (let(150)))) +
            (((let(444)) < (var("x3"))) >= ((var("x3")) * (let(338))))) &&
           ((((var("x0")) && (let(214))) && ((let(208)) + (let(789)))) &&
            (((let(519)) - (var("x3"))) <= ((var("x1")) != (var("x3"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 195},
                   {"x1", 321},
                   {"x2", 808},
                   {"x3", 951},
                   {"x4", 74},
                   {"x5", 920},
                   {"x6", 477}};
    auto expr =
        (((((((var("x3")) > (var("x4"))) != ((let(174)) >= (var("x6")))) -
            (((let(688)) >= (let(86))) || ((var("x6")) != (var("x4"))))) -
           ((((let(718)) >= (var("x0"))) >= ((var("x5")) != (var("x5")))) ==
            (((let(724)) + (var("x3"))) >= ((let(159)) || (let(459)))))) ||
          (((((let(78)) - (let(291))) || ((let(787)) == (var("x5")))) <
            (((var("x6")) != (let(352))) && ((var("x2")) > (let(994))))) +
           ((((let(884)) > (var("x5"))) || ((let(21)) - (let(707)))) -
            (((let(873)) < (var("x4"))) + ((let(685)) * (var("x6"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 308},
                   {"x1", 859},
                   {"x2", 824},
                   {"x3", 927},
                   {"x4", 504},
                   {"x5", 231},
                   {"x6", 644}};
    auto expr =
        (((((((let(813)) != (let(415))) * ((let(88)) && (var("x2")))) +
            (((let(693)) < (var("x5"))) >= ((var("x6")) < (var("x3"))))) <=
           ((((let(653)) == (var("x6"))) <= ((var("x6")) < (var("x6")))) !=
            (((let(243)) && (let(964))) - ((let(962)) <= (let(547)))))) !=
          (((((var("x0")) == (let(693))) - ((var("x2")) > (var("x4")))) -
            (((var("x0")) + (var("x2"))) < ((var("x6")) || (let(367))))) <
           ((((var("x3")) >= (let(276))) + ((var("x3")) < (let(491)))) >
            (((let(576)) > (var("x2"))) <= ((var("x6")) > (var("x3"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 199},
                   {"x1", 828},
                   {"x2", 592},
                   {"x3", 256},
                   {"x4", 891},
                   {"x5", 431},
                   {"x6", 334}};
    auto expr =
        (((((((var("x4")) < (let(563))) && ((var("x6")) != (var("x4")))) ==
            (((var("x6")) <= (let(157))) < ((var("x6")) > (let(226))))) +
           ((((let(421)) && (let(177))) >= ((var("x4")) == (var("x2")))) ==
            (((var("x0")) <= (let(975))) && ((let(789)) + (var("x1")))))) >=
          (((((let(958)) > (var("x2"))) > ((var("x5")) >= (var("x6")))) &&
            (((var("x2")) <= (let(936))) < ((let(668)) + (var("x2"))))) !=
           ((((let(783)) <= (var("x2"))) + ((let(937)) || (let(849)))) ||
            (((var("x6")) >= (var("x4"))) >= ((let(437)) * (var("x3"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 197},
                   {"x1", 392},
                   {"x2", 246},
                   {"x3", 863},
                   {"x4", 864},
                   {"x5", 50},
                   {"x6", 924}};
    auto expr =
        (((((((var("x6")) && (var("x0"))) < ((let(258)) || (var("x1")))) +
            (((var("x1")) * (var("x0"))) == ((let(822)) != (var("x5"))))) <
           ((((let(507)) > (let(362))) || ((var("x0")) * (let(203)))) <=
            (((var("x5")) < (let(765))) + ((let(459)) == (var("x5")))))) &&
          (((((var("x3")) <= (var("x6"))) * ((var("x4")) * (let(474)))) +
            (((let(525)) == (var("x4"))) * ((var("x6")) >= (let(937))))) <
           ((((var("x4")) || (var("x4"))) || ((var("x6")) - (let(115)))) &&
            (((var("x2")) + (let(854))) + ((var("x2")) >= (var("x0"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 318},
                   {"x1", 395},
                   {"x2", 485},
                   {"x3", 857},
                   {"x4", 299},
                   {"x5", 329},
                   {"x6", 836}};
    auto expr =
        (((((((var("x1")) - (var("x5"))) && ((var("x3")) && (var("x3")))) +
            (((let(127)) * (let(982))) && ((let(389)) || (var("x4"))))) >=
           ((((let(799)) - (var("x4"))) <= ((let(994)) - (var("x0")))) &&
            (((var("x2")) == (let(740))) - ((var("x0")) * (let(778)))))) ||
          (((((let(154)) < (var("x4"))) <= ((var("x4")) < (var("x3")))) !=
            (((var("x6")) < (let(21))) || ((let(607)) >= (let(293))))) ==
           ((((var("x4")) * (let(615))) > ((let(593)) * (let(884)))) &&
            (((let(248)) || (let(534))) + ((let(936)) <= (var("x1"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 1);
  }

  {
    State state = {{"x0", 27},
                   {"x1", 325},
                   {"x2", 453},
                   {"x3", 861},
                   {"x4", 933},
                   {"x5", 200},
                   {"x6", 228}};
    auto expr =
        (((((((let(884)) <= (let(543))) < ((let(51)) <= (var("x1")))) +
            (((let(892)) != (var("x5"))) || ((var("x5")) >= (let(757))))) >
           ((((var("x1")) != (var("x0"))) && ((let(903)) * (let(577)))) >=
            (((let(157)) && (var("x2"))) == ((let(45)) >= (var("x2")))))) <
          (((((let(579)) <= (var("x0"))) && ((let(576)) || (var("x2")))) <=
            (((var("x3")) <= (let(556))) || ((let(620)) - (var("x1"))))) *
           ((((let(984)) * (var("x0"))) - ((let(708)) != (let(151)))) >
            (((var("x1")) == (let(696))) || ((let(599)) < (var("x4"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 290},
                   {"x1", 252},
                   {"x2", 353},
                   {"x3", 334},
                   {"x4", 83},
                   {"x5", 906},
                   {"x6", 968}};
    auto expr =
        (((((((var("x6")) * (var("x1"))) || ((var("x5")) < (let(970)))) +
            (((let(148)) < (var("x6"))) * ((let(382)) && (var("x1"))))) <
           ((((var("x2")) <= (var("x5"))) > ((var("x5")) != (var("x6")))) ==
            (((var("x0")) == (var("x3"))) < ((let(782)) - (var("x5")))))) +
          (((((let(746)) && (var("x3"))) && ((let(213)) * (let(411)))) >=
            (((var("x3")) < (let(207))) * ((var("x6")) > (let(428))))) ==
           ((((var("x2")) || (var("x6"))) != ((let(337)) - (let(365)))) *
            (((let(147)) >= (let(774))) && ((var("x2")) >= (let(971))))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 371},
                   {"x1", 966},
                   {"x2", 726},
                   {"x3", 574},
                   {"x4", 138},
                   {"x5", 659},
                   {"x6", 962}};
    auto expr =
        (((((((let(538)) != (var("x1"))) <= ((let(919)) - (let(290)))) *
            (((let(544)) >= (let(35))) > ((var("x4")) && (var("x5"))))) ||
           ((((let(574)) || (let(487))) * ((let(858)) - (let(129)))) -
            (((let(704)) || (let(34))) < ((var("x1")) <= (var("x6")))))) *
          (((((var("x1")) >= (let(583))) && ((var("x1")) != (var("x5")))) <
            (((var("x1")) != (let(261))) * ((var("x2")) >= (var("x0"))))) +
           ((((var("x2")) + (let(515))) * ((let(127)) * (let(360)))) <
            (((var("x4")) || (var("x4"))) == ((var("x4")) < (var("x5"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  {
    State state = {{"x0", 959},
                   {"x1", 997},
                   {"x2", 989},
                   {"x3", 236},
                   {"x4", 386},
                   {"x5", 72},
                   {"x6", 932},
                   {"x7", 473}};
    auto expr =
        (((((((var("x6")) > (let(282))) || ((let(369)) * (let(260)))) <
            (((var("x5")) && (let(23))) < ((let(637)) <= (var("x7"))))) +
           ((((var("x2")) || (let(68))) <= ((var("x5")) >= (var("x2")))) -
            (((let(571)) || (var("x3"))) - ((var("x6")) <= (let(915)))))) >
          (((((let(260)) || (let(348))) > ((let(809)) + (var("x5")))) <
            (((var("x5")) >= (var("x7"))) * ((var("x6")) - (var("x1"))))) !=
           ((((let(280)) <= (var("x4"))) < ((var("x5")) == (var("x7")))) <
            (((var("x2")) > (let(511))) - ((var("x2")) < (var("x4"))))))));
    auto result = expr->eval(state);
    assert(result && *result == 0);
  }

  return 0;
}
