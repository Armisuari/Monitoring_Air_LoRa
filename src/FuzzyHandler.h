#pragma once

#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();

FuzzyInput *distance = new FuzzyInput(1);
FuzzySet *pendek = new FuzzySet(0, 7, 15, 22);
FuzzySet *sedang = new FuzzySet(18, 25, 33, 40);
FuzzySet *tinggi = new FuzzySet(36, 43, 51, 58);
FuzzySet *stinggi = new FuzzySet(54, 63, 71, 80);

FuzzyOutput *servo = new FuzzyOutput(1);
FuzzySet *aman = new FuzzySet(0, 9, 19, 28);
FuzzySet *siaga = new FuzzySet(25, 34, 44, 53);
FuzzySet *bahaya = new FuzzySet(50, 59, 69, 78);
FuzzySet *banjir = new FuzzySet(75, 83, 92, 100);

// fuzzy rules

FuzzyRuleAntecedent *ifDistancePendek = new FuzzyRuleAntecedent();
FuzzyRuleConsequent *thenServoAman = new FuzzyRuleConsequent();
FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifDistancePendek, thenServoAman);

FuzzyRuleAntecedent *ifDistanceSedang = new FuzzyRuleAntecedent();
FuzzyRuleConsequent *thenServoSiaga = new FuzzyRuleConsequent();
FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifDistanceSedang, thenServoSiaga);

FuzzyRuleAntecedent *ifDistanceTinggi = new FuzzyRuleAntecedent();
FuzzyRuleConsequent *thenServoBahaya = new FuzzyRuleConsequent();
FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifDistanceTinggi, thenServoBahaya);

FuzzyRuleAntecedent *ifDistanceSTinggi = new FuzzyRuleAntecedent();
FuzzyRuleConsequent *thenServoBanjir = new FuzzyRuleConsequent();
FuzzyRule *fuzzyRule04 = new FuzzyRule(4, ifDistanceSTinggi, thenServoBanjir);

void fuzzy_input()
{
  distance->addFuzzySet(pendek);
  distance->addFuzzySet(sedang);
  distance->addFuzzySet(tinggi);
  distance->addFuzzySet(stinggi);
  fuzzy->addFuzzyInput(distance);
}

void fuzzy_output()
{
  servo->addFuzzySet(aman);
  servo->addFuzzySet(siaga);
  servo->addFuzzySet(bahaya);
  servo->addFuzzySet(banjir);
  fuzzy->addFuzzyOutput(servo);
}

void fuzzy_rules()
{
  ifDistancePendek->joinSingle(pendek);
  thenServoAman->addOutput(aman);
  fuzzy->addFuzzyRule(fuzzyRule01);

  ifDistanceSedang->joinSingle(sedang);
  thenServoSiaga->addOutput(siaga);
  fuzzy->addFuzzyRule(fuzzyRule02);

  ifDistanceTinggi->joinSingle(tinggi);
  thenServoBahaya->addOutput(bahaya);
  fuzzy->addFuzzyRule(fuzzyRule03);

  ifDistanceSTinggi->joinSingle(stinggi);
  thenServoBanjir->addOutput(banjir);
  fuzzy->addFuzzyRule(fuzzyRule04);
}

void setup_fuzzy()
{
    // randomSeed(analogRead(0));

    fuzzy_input();
    fuzzy_output();
    fuzzy_rules();
}