#include <eflib/include/platform/disable_warnings.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Support/StandardPasses.h>
#include <llvm/Support/raw_os_ostream.h>
#include <eflib/include/platform/enable_warnings.h>

#include <sasl/include/code_generator/llvm/cgllvm_api.h>

#include <eflib/include/platform/boost_begin.h>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <eflib/include/platform/boost_end.h>

#include <vector>

using llvm::Function;
using llvm::FunctionPassManager;
using llvm::Module;
using llvm::PrintMessageAction;
using llvm::raw_os_ostream;
using llvm::verifyFunction;

using boost::shared_ptr;

using std::vector;
using std::ostream;

BEGIN_NS_SASL_CODE_GENERATOR();

void optimize( shared_ptr<llvm_code> code, vector<optimization_options> opt_options )
{
	Module* mod = code->module();

	FunctionPassManager fpm(mod);

	BOOST_FOREACH( optimization_options opt_option, opt_options ){
		switch ( opt_option ){
			case opt_verify:
				BOOST_FOREACH( Function& f, mod->getFunctionList() ){
					if(!f.empty()){
						verifyFunction(f, PrintMessageAction);
					}
				}
				break;
			case opt_preset_std_for_function:
				createStandardFunctionPasses( &fpm, 1 );
				break;
		}
	}

	fpm.doInitialization();

	BOOST_FOREACH( Function& f, mod->getFunctionList() ){
		if(!f.empty()){
			fpm.run(f);
		}
	}
}

void dump( shared_ptr<llvm_code> code )
{
	code->module()->dump();
}

void dump( shared_ptr<llvm_code> code, ostream& o ){
	raw_os_ostream raw_os(o);
	code->module()->print( raw_os, NULL );
	raw_os.flush();
}

END_NS_SASL_CODE_GENERATOR();