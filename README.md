# CBMI
## c implemented brainfuck like language interpreter

# interpreter features
the interpreter features only these following options:\
--help     prints all accepted commands\
--info     prints some info about e.g. filesize restrictions\
<filename> the file which to interpret



# language features
its a superset to brainf*ck with identifiers.\
to declare an identifier write something like that:

`def <identifier_name> = <brainf*ck_code>;`\
for example:\
`def letter_A = ++++++++++[>++++++<-]>+++++.;`\
an identifier must comply regex `[a-zA-Z_]{9}`\
code named by an identifier must not contain open loops.\
This will not work:\
`def half_loop = +++[>+++; // ERROR`

to reference an identifier prefix it with \* within regular brainf*ck code:\
`def letter_A = ++++++++++[>++++++<-]>+++++.;`\
`*letter_A>++++++++++[>+++<-]>+++.`
which prints 'A!'.

