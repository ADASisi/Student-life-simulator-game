#pragma once

void checkVariable(int& variable) {
    if (variable > 100) {
        variable = 100;
    }
}

void checkParameters(int& energy, int& knowledge, int& mentality) {
    checkVariable(energy);
    checkVariable(knowledge);
    checkVariable(mentality);
}
