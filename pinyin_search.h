#ifndef  _PINYIN_SEARCH_H_
#define  _PINYIN_SEARCH_H_


#define  USER_UNICODE_UTF8      1     //使用 UTF-8 编码
#define  USER_UNICODE_GBK2312   0   //使用 GBK2312 编码

#define  USER_UNICODE_MODE  USER_UNICODE_UTF8  // USER_UNICODE_UN_UTF8

const char* pinyin_search(char* str_input_str, int* num);

#endif
