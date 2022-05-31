#include <iostream>
#include <memory>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/DIBuilder.h"

#include "modmk.h"

llvm::Function* defineFunc(llvm::IRBuilder<>* builder, llvm::Module* m) {
	std::vector<llvm::Type*> fta2(2, llvm::Type::getDoubleTy(builder->getContext()));
	llvm::FunctionType* ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(builder->getContext()), fta2, false);
	llvm::Function* f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "func", m);
	llvm::BasicBlock* fb = llvm::BasicBlock::Create(m->getContext(), "entry", f);
	builder->SetInsertPoint(fb);

	//llvm::Value* a = llvm::ConstantFP::get(*vm_context, llvm::APFloat(12.34));
	//llvm::Value* b = llvm::ConstantFP::get(*vm_context, llvm::APFloat(56.78));
	llvm::Value* a = f->getArg(0);
	llvm::Value* b = f->getArg(1);
	llvm::Value* c = builder->CreateFAdd(a, b, "addtmp");
	// llvm::Value* c = ir_builder->CreateBinOp(llvm::Instruction::FAdd, a, b);
	// c->print(llvm::errs());

	builder->CreateRet(c);
	llvm::verifyFunction(*f);
	return f;
}

int make_func() {
	std::unique_ptr<llvm::LLVMContext> vm_context = std::make_unique<llvm::LLVMContext>();
	std::unique_ptr<llvm::Module> vm_module = std::make_unique<llvm::Module>("my cool jit", *vm_context);
	std::unique_ptr<llvm::IRBuilder<>> ir_builder = std::make_unique<llvm::IRBuilder<>>(*vm_context);

	auto f = defineFunc(ir_builder.get(), vm_module.get());

	vm_module->print(llvm::outs(), nullptr);

	/*std::unique_ptr<llvm::DIBuilder> di_builder = std::make_unique<llvm::DIBuilder>(*vm_module);

	auto dbginfo = di_builder->createCompileUnit(
		llvm::dwarf::DW_LANG_C, di_builder->createFile("fib.ks", "."),
		"Kaleidoscope Compiler", false, "", 0);

	di_builder->finalize();*/

	for (auto& f : vm_module->getFunctionList()) {
		f.removeFromParent();
	}
	
	int aa;
	std::cin >> aa;
	return 0;
}