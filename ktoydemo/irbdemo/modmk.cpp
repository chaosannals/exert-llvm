
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

int make_module() {
    LLVMContext &Context = *new LLVMContext();

    // Create the "module" or "program" or "translation unit" to hold the
    // function
    Module* M = new Module("test", Context);

    // Create the main function: first create the type 'int ()'
    FunctionType* FT =
        FunctionType::get(Type::getInt32Ty(Context), /*not vararg*/false);

    // By passing a module as the last parameter to the Function constructor,
    // it automatically gets appended to the Module.
    Function* F = Function::Create(FT, Function::ExternalLinkage, "main", M);

    // Add a basic block to the function... again, it automatically inserts
    // because of the last argument.
    BasicBlock* BB = BasicBlock::Create(Context, "EntryBlock", F);

    // Get pointers to the constant integers...
    Value* Two = ConstantInt::get(Type::getInt32Ty(Context), 2);
    Value* Three = ConstantInt::get(Type::getInt32Ty(Context), 3);

    // Create the add instruction... does not insert...
    Instruction* Add = BinaryOperator::Create(Instruction::Add, Two, Three,
        "addresult");

    // explicitly insert it into the basic block...
    BB->getInstList().push_back(Add);

    // Create the return instruction and add it to the basic block
    BB->getInstList().push_back(ReturnInst::Create(Context, Add));

    // Output the bitcode file to stdout
    // WriteBitcodeToFile(*M, outs());
    
    outs() << "\n\n----------------------\n\n";
    M->print(outs(), nullptr);

    // Delete the module and all of its contents.
    
    // 可能是这版本的 bug ，需要手动 removeFromParent 模块定义的函数。
    M->dropAllReferences();
    F->removeFromParent();
    // F->eraseFromParent(); // 官方示例使用，但是报错，不可用。
    // delete F; // 删除不可用
    // 下面的循环不可用，必须自己管理函数对象。
    /*
    for (auto& f : M->getFunctionList()) {
        outs() << f.getName() << " delete\n\n";
        f.removeFromParent();
    }
    */
    


    delete M;
    delete &Context;
    return 0;
}