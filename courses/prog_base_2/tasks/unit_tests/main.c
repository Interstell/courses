#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>
#include <cmocka_pbc.h>
#include "text.h"

static void create_void_zeroCount(void **state){
	text_t text = text_create();
	assert_int_equal(text_getSentenceAmount(text), 0);
}

static void addSentenceToEnd_oneString_countOne(void **state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST");
	assert_int_equal(text_getSentenceAmount(text), 1);
}

static void addSentenceToEnd__nullSentencePointer__putsNULL_POINTERtoStatus(void** state){
	text_t text = text_create();
	text_addSentenceToEnd(text, NULL);
	assert_int_equal(text_getStatus(text), NULL_POINTER);
}

static void addSentenceByIndex_hasTwoAddedSentencesAddingOneNewSentenceToZeroIndex_testIfWasAdded(void** state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST1");
	text_addSentenceToEnd(text, "TEST2");
	text_addSentenceByIndex(text, "TEST0", 0);
	assert_string_equal(text_getSentence(text, 0), "TEST0");
}

static void addSentenceByIndex_hasTwoAddedSentencesAddingOneNewSentenceToIndexOne_testIfWasAdded(void **state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST1");
	text_addSentenceToEnd(text, "TEST2");
	text_addSentenceByIndex(text, "TESTMIDDLE", 1);
	assert_string_equal(text_getSentence(text, 1), "TESTMIDDLE");
}

static void addSentenceByIndex__NonExistingIndex__putsINDEX_OUT_OF_BOUNDtoStatus(void **state){
	text_t text = text_create(); 
	text_addSentenceByIndex(text, "NONEXISTINGINDEX", 100500);
	assert_int_equal(text_getStatus(text), INDEX_OUT_OF_BOUND);
}

static void addSentenceByIndex__nullSentencePointer__putsNULL_POINTERtoStatus(void** state){
	text_t text = text_create();
	text_addSentenceByIndex(text, NULL, 0);
	assert_int_equal(text_getStatus(text), NULL_POINTER);
}

static void setSentenceByIndex__NonExistingIndex__putsINDEX_OUT_OF_BOUNDtoStatus(void **state){
	text_t text = text_create();
	text_setSentenceByIndex(text, "NONEXISTINGINDEX", -100500);
	assert_int_equal(text_getStatus(text), INDEX_OUT_OF_BOUND);
}

static void setSentenceByIndex__nullSentencePointer__putsNULL_POINTERtoStatus(void** state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST1");
	text_setSentenceByIndex(text, NULL, 0);
	assert_int_equal(text_getStatus(text), NULL_POINTER);
}

static void setSentenceByIndex_hasOneAddedSentenceSettingNewSentenceInstead_testIfHasChanged(void **state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST1");
	text_setSentenceByIndex(text, "REPLACED", 0);
	assert_string_equal(text_getSentence(text, 0), "REPLACED");
}

static void deleteSentenceByIndex_hasOneAddedSentenceDeletingIt_zeroCount(void **state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST1");
	text_deleteSentenceByIndex(text, 0);
	assert_int_equal(text_getSentenceAmount(text), 0);
}

static void deleteSentenceByIndex__DeletingNonExistingIndex__putsINDEX_OUT_OF_BOUNDtoStatus(void **state){
	text_t text = text_create();
	text_deleteSentenceByIndex(text, -100500);
	assert_int_equal(text_getStatus(text), INDEX_OUT_OF_BOUND);
}

static void getSentence_hasOneAddedSentence_returnsAddedSentence(void **state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TESTSTR");
	assert_string_equal(text_getSentence(text, 0), "TESTSTR");
}

static void getText_hasThreeAddedSentences_returnsText(void** state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST1");
	text_addSentenceToEnd(text, "TEST2");
	text_addSentenceToEnd(text, "TEST3");
	assert_string_equal(text_getText(text), "TEST1. TEST2. TEST3. ");
}

static void getSentenceAmount_hasThreeAddedSentences_returnsCount(void **state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST1");
	text_addSentenceToEnd(text, "TEST2");
	text_addSentenceToEnd(text, "TEST3");
	assert_int_equal(text_getSentenceAmount(text), 3);
}

static void getWordsAmountInText_hasSomeAddedSentences_returnsWordsCount(void **state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "ababa ajjkasd");
	text_addSentenceToEnd(text, "asd+sd");
	text_addSentenceToEnd(text, "ababa gala&maga");
	assert_int_equal(text_getWordsAmountInText(text), 7);
}

static void getStatus__callingNULL_POINTERerror__returnStatus(void **state){
	text_t text = text_create();
	text_addSentenceByIndex(text, NULL, 0);
	assert_int_equal(text_getStatus(text), NULL_POINTER);
}

static void getStatus__callingINDEX_OUT_OF_BOUNDerror__returnStatus(void **state){
	text_t text = text_create();
	text_addSentenceByIndex(text, "TEST", 100500);
	assert_int_equal(text_getStatus(text), INDEX_OUT_OF_BOUND);
}

static void getStatus__addingNon_NULLsentenceToProperIndexToGetOKstatus__returnStatus(void** state){
	text_t text = text_create();
	text_addSentenceToEnd(text, "TEST");
	assert_int_equal(text_getStatus(text), OK);
}

void runTests(void){
	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(create_void_zeroCount),
		cmocka_unit_test(addSentenceToEnd_oneString_countOne),
		cmocka_unit_test(addSentenceByIndex_hasTwoAddedSentencesAddingOneNewSentenceToZeroIndex_testIfWasAdded),
		cmocka_unit_test(addSentenceByIndex_hasTwoAddedSentencesAddingOneNewSentenceToIndexOne_testIfWasAdded),
		cmocka_unit_test(addSentenceByIndex__NonExistingIndex__putsINDEX_OUT_OF_BOUNDtoStatus),
		cmocka_unit_test(addSentenceByIndex__nullSentencePointer__putsNULL_POINTERtoStatus),
		cmocka_unit_test(addSentenceToEnd__nullSentencePointer__putsNULL_POINTERtoStatus),
		cmocka_unit_test(setSentenceByIndex_hasOneAddedSentenceSettingNewSentenceInstead_testIfHasChanged),
		cmocka_unit_test(setSentenceByIndex__NonExistingIndex__putsINDEX_OUT_OF_BOUNDtoStatus),
		cmocka_unit_test(setSentenceByIndex__nullSentencePointer__putsNULL_POINTERtoStatus),
		cmocka_unit_test(deleteSentenceByIndex_hasOneAddedSentenceDeletingIt_zeroCount),
		cmocka_unit_test(deleteSentenceByIndex__DeletingNonExistingIndex__putsINDEX_OUT_OF_BOUNDtoStatus),
		cmocka_unit_test(getSentence_hasOneAddedSentence_returnsAddedSentence),
		cmocka_unit_test(getText_hasThreeAddedSentences_returnsText),
		cmocka_unit_test(getSentenceAmount_hasThreeAddedSentences_returnsCount),
		cmocka_unit_test(getWordsAmountInText_hasSomeAddedSentences_returnsWordsCount),
		cmocka_unit_test(getStatus__callingNULL_POINTERerror__returnStatus),
		cmocka_unit_test(getStatus__callingINDEX_OUT_OF_BOUNDerror__returnStatus),
		cmocka_unit_test(getStatus__addingNon_NULLsentenceToProperIndexToGetOKstatus__returnStatus),

	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}

int main(void) {
	runTests();
	getchar();
}