/* keyword.h
token-test.cで対象とするキーワードの定義ファイル　*/

/* キーワードの個数の定義　*/
#define NUMKW 7

/* キーワードの識別子の定義　*/
typedef enum{
_clear,_decode,_exec,_load,_mem,_step,_trace
} KeyId;

/* キーワード定義表　*/
static KeyWD KWDT[NUMKW] = {
{"clear",_clear},{"decode",_decode},{"exec",_exec},
{"load",_load},{"mem",_mem}, {"step",_step}, {"trace",_trace}
};
