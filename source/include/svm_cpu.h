//
// Created by swift on 2021/5/26.
//

#pragma once

#include "svm_instance.h"

namespace Svm {

    class CPUContext;

    class VCpu : CopyDisable {
    public:

        explicit VCpu(SvmInstance *instance);

        virtual ~VCpu();

        void Run(u64 ticks = 0);

        void Halt();

        void SetPC(VAddr pc);

        u8 *GeneralRegRef(int index);

        u8 *VectorRegRef(int index);

        VAddr GetPC();

        virtual void CallSvc(u32 num) {
            abort();
        };

        virtual void CallHlt(u32 num) {
            abort();
        };

        virtual void CallBrk(u32 num) {
            abort();
        };

        virtual void Yield() {};

        virtual void Fallback() {
            abort();
        };

        virtual void PageFatal(VAddr va, u8 flags) {
            abort();
        };

        virtual void IllegalCode(VAddr va) {
            abort();
        };

        constexpr SvmInstance &Instance() {
            return *instance;
        }

        constexpr CPUContext *Context() {
            return context;
        }

        constexpr bool HasInterrupt() {
            return interrupt;
        }

        constexpr void MarkInterrupt() {
            interrupt = true;
        }

        void ClearInterrupt();

        constexpr void MakeInterFastReturn() {
            interrupt_fast_ret = true;
        }

        constexpr bool IsInterFastReturn() {
            auto res = interrupt_fast_ret.load();
            interrupt_fast_ret = false;
            return res;
        }

    private:
        SvmInstance *instance{};
        CPUContext *context{};
        CpuArch arch{};
        std::atomic_bool interrupt{};
        std::atomic_bool interrupt_fast_ret{false};
    };

}
