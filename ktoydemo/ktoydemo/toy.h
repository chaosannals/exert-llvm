#pragma once
#include <map>
#include <istream>
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

void InitializeModule();
void MainLoop();

namespace ktoy {
	class toylang {
		std::unique_ptr<llvm::LLVMContext> vm_context;
		std::unique_ptr<llvm::Module> vm_module;
		std::unique_ptr<llvm::IRBuilder<>> ir_builder;
		std::map<std::string, llvm::Value*> named_values;
	public:
		void initialize();
		void interpret(std::istream& input);
	};
}