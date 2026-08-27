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
    
    # 🔥 CRITICAL FIX: Generate PROVEN working copy mechanism instead of experimental API!
    js_string_code = (code
                      .replace('\\', '\\\\')    # Escape backslashes first
                      .replace('`', '\\`'))     # Only need to escape backticks for template literals

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
<!-- 🔥 CRITICAL FIX: Use proven legacy copy mechanism instead of experimental clipboard API -->
<button class="copy-btn" onclick="legacyCopyCode(this)">Copy Code</button>
</div>

<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/components/prism-core.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/plugins/autoloader/prism-autoloader.min.js"></script>

<!-- 🔥 CRITICAL FIX: Include proven working copy function -->
<script>
function legacyCopyCode(button) {{
    // 🎯 EXACTLY replicate your originally-working approach from manual HTML file!
    const codeBlock = button.previousElementSibling;  // Get the <pre><code> element
    
    // Extract clean text content (handles HTML entities automatically)
    const tempDiv = document.createElement('div');
    tempDiv.innerHTML = codeBlock.innerHTML;
    const textToCopy = tempDiv.textContent || tempDiv.innerText || '';
    
    // 🔥 CORE WORKING MECHANISM: Create textarea + execCommand approach
    const textarea = document.createElement("textarea");
    textarea.value = textToCopy;
    textarea.style.position = "fixed";  // Prevent scrolling to bottom
    textarea.style.opacity = "0";       // Keep invisible but focusable
    document.body.appendChild(textarea);
    textarea.focus();
    textarea.select();
    
    try {{
        const successful = document.execCommand('copy');  // Universal browser support!
        if (successful) {{
            button.textContent = "✅ Copied!";
        }} else {{
            throw new Error("execCommand returned false");
        }}
    }} catch (err) {{
        console.error('Copy failed:', err);
        button.textContent = "❌ Manual Copy Required";
        // Highlight code for manual selection as fallback
        const range = document.createRange();
        range.selectNode(codeBlock.querySelector('code') || codeBlock);
        window.getSelection().removeAllRanges();
        window.getSelection().addRange(range);
    }} finally {{
        setTimeout(() => {{
            button.textContent = "Copy Code";  // Restore original text
            if (document.body.contains(textarea)) {{
                document.body.removeChild(textarea);  // Cleanup
            }}
        }}, 2000);
    }}
}}
</script>

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
