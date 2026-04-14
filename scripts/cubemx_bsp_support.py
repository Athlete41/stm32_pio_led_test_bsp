# scripts/cubemx_bsp_support.py
"""
适用于 STM32CubeMX 生成的裸机配置代码。
将 Core/Inc 和 Core/Src 中的文件全部拷贝到项目根目录下的 Init 文件夹（平铺），
并重命名 main.c -> stm32_init.c，main.h -> stm32_init.h，
修改函数名、while 循环、宏保护及所有 #include "main.h" 引用。
注意：此脚本假设 CubeMX 项目结构为标准 Core/Inc 和 Core/Src，其他情况未测试。
"""

import re
import shutil
from pathlib import Path
import os

Import("env")

def copy_and_modify_core_to_init(core_dir):
    """将 Core/Inc 和 Core/Src 中的所有文件平铺拷贝到 Init 目录，并修改内容"""
    project_dir = Path(env.subst("$PROJECT_DIR"))
    core_path = project_dir / core_dir
    init_path = core_path.parent / "Init"

    # 检查 Core 目录
    if not core_path.exists():
        print(f"[SCRIPT] Core directory not found: {core_path}")
        return False

    # 删除已存在的 Init 目录（完全重新生成）
    if init_path.exists():
        shutil.rmtree(init_path)
        print(f"[SCRIPT] Removed existing Init directory: {init_path}")

    init_path.mkdir(parents=True, exist_ok=True)

    # 拷贝 Inc 和 Src 中的所有文件到 Init 根目录（平铺）
    inc_src = core_path / "Inc"
    src_src = core_path / "Src"

    def copy_files_to_init(source_dir):
        if source_dir.exists():
            for file in source_dir.iterdir():
                if file.is_file():
                    dst = init_path / file.name
                    shutil.copy2(file, dst)
                    print(f"[SCRIPT] Copied {file} -> {dst}")
        else:
            print(f"[SCRIPT] Warning: directory not found: {source_dir}")

    copy_files_to_init(inc_src)
    copy_files_to_init(src_src)

    # 修改 stm32_init.c (原 main.c)
    main_c = init_path / "main.c"
    stm32_c = init_path / "stm32_init.c"
    if main_c.exists():
        with open(main_c, 'r', encoding='utf-8') as f:
            content = f.read()
        # 1. 修改函数名 main -> STM32_Init
        content = re.sub(r'\bint\s+main\s*\(', 'int STM32_Init(', content)
        # 2. while(1) -> while(0)
        content = re.sub(r'while\s*\(\s*1\s*\)', 'while(0)', content)
        # 3. 包含头文件
        content = re.sub(r'#include\s+"main\.h"', '#include "stm32_init.h"', content)
        with open(stm32_c, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"[SCRIPT] Created: {stm32_c}")
        main_c.unlink()  # 删除原 main.c
    else:
        print(f"[SCRIPT] main.c not found in Init")

    # 修改 stm32_init.h (原 main.h)
    main_h = init_path / "main.h"
    stm32_h = init_path / "stm32_init.h"
    if main_h.exists():
        with open(main_h, 'r', encoding='utf-8') as f:
            content = f.read()
        # 宏保护
        content = re.sub(r'#ifndef __MAIN_H', '#ifndef __STM32_INIT_H', content)
        content = re.sub(r'#define __MAIN_H', '#define __STM32_INIT_H', content)
        # 函数声明
        content = re.sub(r'int\s+main\s*\(void\s*\);', 'int STM32_Init(void);', content)
        # 在 Error_Handler 下方添加 STM32_Init 声明
        pattern = r'(void\s+Error_Handler\s*\(void\s*\);)\s*'
        replacement = r'\1\nint STM32_Init(void);\n'
        if re.search(pattern, content):
            content = re.sub(pattern, replacement, content, count=1)
        else:
            content += '\n\nint STM32_Init(void);\n'
        with open(stm32_h, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"[SCRIPT] Created: {stm32_h}")
        main_h.unlink()
    else:
        print(f"[SCRIPT] main.h not found in Init")

    # 全局替换：将所有 .c/.h 中的 #include "main.h" 改为 #include "stm32_init.h"
    for ext in ('*.c', '*.h'):
        for file_path in init_path.glob(ext):
            # 跳过刚生成的 stm32_init 文件
            if file_path.name in ('stm32_init.c', 'stm32_init.h'):
                continue
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            if '#include "main.h"' in content:
                new_content = re.sub(r'#include\s+"main\.h"', '#include "stm32_init.h"', content)
                with open(file_path, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                print(f"[SCRIPT] Replaced #include in: {file_path}")

    print("[SCRIPT] Init directory generation complete.")
    return True

def process_cubemx_files(env):
    core_dir = env.GetProjectOption('cubemx_core_dir')
    if not core_dir:
        print("[SCRIPT] Warning: cubemx_core_dir not set, skipping.")
        return
    copy_and_modify_core_to_init(core_dir)

print('================== start process cubemx files ==================')
process_cubemx_files(env)
print('================== end process cubemx files ==================')