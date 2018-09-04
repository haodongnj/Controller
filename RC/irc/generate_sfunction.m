% setenv('MW_MINGW64_LOC','C:\mingw64')

myFunctionName = 'RC_PLL';

def = legacy_code('initialize');
def.SFunctionName = myFunctionName ;
def.OutputFcnSpec = 'double y1 = irc_update_simulink(double u1, double u2)';
def.HeaderFiles = {'irc.h', 'filter.h'};
def.SourceFiles = {'irc.c', 'filter.c'};
def.InitializeConditionsFcnSpec = 'irc_init_simulink()';

legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def) ;