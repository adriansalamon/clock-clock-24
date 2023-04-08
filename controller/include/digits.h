#ifndef DIGITS_H
#define DIGITS_H

#include "clock_state.h"

const t_digit digit_0 = {
    90, 180,
    0, 180,
    0, 90,
    270, 180,
    0, 180,
    0, 270};

const t_digit digit_1 = {
    225, 225,
    225, 225,
    225, 225,
    180, 180,
    0, 180,
    0, 0};

const t_digit digit_2 = {
    90, 90,
    90, 180,
    0, 90,
    270, 180,
    0, 270,
    270, 270};

const t_digit digit_3 = {
    90, 90,
    90, 90,
    90, 90,
    270, 180,
    0, 270,
    0, 270};

const t_digit digit_4 = {
    180, 180,
    0, 90,
    225, 225,
    180, 180,
    0, 180,
    0, 0};

const t_digit digit_5 = {
    90, 180,
    0, 90,
    90, 90,
    270, 270,
    180, 270,
    0, 270};

const t_digit digit_6 = {
    90, 180,
    0, 180,
    0, 90,
    270, 270,
    180, 270,
    0, 270};

const t_digit digit_7 = {
    90, 90,
    225, 225,
    225, 225,
    270, 180,
    0, 180,
    0, 0};

const t_digit digit_8 = {
    90, 180,
    0, 90,
    0, 90,
    270, 180,
    0, 270,
    0, 270};

const t_digit digit_9 = {
    90, 180,
    0, 90,
    90, 90,
    270, 180,
    0, 180,
    0, 270};

const t_digit digits[10] = {
    digit_0,
    digit_1,
    digit_2,
    digit_3,
    digit_4,
    digit_5,
    digit_6,
    digit_7,
    digit_8,
    digit_9};

const t_digit digit_I = {
    270, 90,
    270, 90,
    270, 90,
    270, 90,
    270, 90,
    270, 90};

const t_digit digit_null = {
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0};

const t_digit digit_happy = {
    45, 315,
    45, 315,
    45, 315,
    45, 315,
    45, 315,
    45, 315};

const t_full_digits clock_null = {digit_null, digit_null, digit_null, digit_null};

const t_full_digits clock_line = {digit_I, digit_I, digit_I, digit_I};

const t_full_digits clock_happy = {digit_happy, digit_happy, digit_happy, digit_happy};

#endif // DIGITS_H