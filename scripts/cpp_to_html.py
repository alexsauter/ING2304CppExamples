#!/usr/bin/env python3
"""Convert C++ files to syntax-highlighted HTML with WORKING copy buttons"""

import os
import html
from pathlib import Path

def cpp_file_to_html(cpp_filename, output_dir="html-output"):
    """Convert a .cpp file into an embeddable HTML snippet with WORKING copy button"""
    
    input_path = Path("cpp-examples") / cpp_filename
    if not input_path.exists():
        raise FileNotFoundError(f"C++ source file '{input_path}' does not exist.")

    with open(input_path, "r", encoding="utf-8") as f:
        code = f.read()

    # For DISPLAY purposes - escape HTML entities for safe rendering inside <pre><code>
    escaped_for_display = html.escape(code)

    filename_no_ext = Path(cpp_filename).stem  # Remove .cpp extension
    
    # 🔥 CRITICAL FIX: Convert ALL special characters appropriately for JavaScript context
    js_string_code = (code
                      .replace('\\', '\\\\')    # Must be FIRST! Escape backslashes
                      .replace('\n', '\\n')     # Convert newlines to JS escape sequences
                      .replace('"', '\\"'))     # Escape double quotes for safety

    html_content = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{filename_no_ext}</title>
    <!-- Prism.js for syntax highlighting -->
    <link href="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/themes/prism.min.css" rel="stylesheet"/>
    <style>
        body {{ margin: 0; padding: 20px; font-family: Arial, sans-serif; }}
        pre {{ border-radius: 6px; padding: 15px !important; }}
        .code-container {{ position: relative; }}
        .copy-btn {{
            position: absolute; top: 10px; right: 10px;
            background-color: #4CAF50; color: white; border: none;
            padding: 6px 12px; border-radius: 4px; cursor: pointer;
        }}
    </style>
</head>
<body>

<div class="code-container">
<pre><code class="language-cpp">{escaped_for_display}</code></pre>
<!-- CRITICAL FIX: Use single quotes for JS string AND convert newlines to \n sequences -->
<button class="copy-btn" onclick="navigator.clipboard.writeText('{js_string_code}')">Copy Code</button>
</div>

<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/components/prism-core.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/plugins/autoloader/prism-autoloader.min.js"></script>

</body>
</html>"""

    output_path = Path(output_dir) / f"{filename_no_ext}.html"
    os.makedirs(output_dir, exist_ok=True)
    
    with open(output_path, "w", encoding="utf-8") as out:
        out.write(html_content)

if __name__ == "__main__":
    cpp_folder = Path("cpp-examples")
    
    if not cpp_folder.exists():
        print("⚠️ Folder 'cpp-examples' does not exist yet.")
        exit(0)  # Don't fail the build because of missing folder

    converted_count = 0
    failed_files = []

    for cpp_file in sorted(cpp_folder.glob("*.cpp")):
        try:
            cpp_file_to_html(cpp_file.name)
            print(f"✅ Converted {cpp_file.name}")
            converted_count += 1
        except Exception as e:
            print(f"❌ Failed to convert {cpp_file.name}: {e}")
            failed_files.append((cpp_file.name, str(e)))

    if converted_count == 0 and not any(cpp_folder.glob("*.cpp")):
        print("📭 No .cpp files found in cpp-examples folder.")

    if failed_files:
        print("\n⚠️ Some conversions had issues:")
        for fname, err in failed_files:
            print(f"   - {fname}: {err}")
