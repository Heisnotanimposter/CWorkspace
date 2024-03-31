{
  "nbformat": 4,
  "nbformat_minor": 0,
  "metadata": {
    "colab": {
      "provenance": [],
      "authorship_tag": "ABX9TyNzLsW4lynCw5+vR3Ue/j0z",
      "include_colab_link": true
    },
    "kernelspec": {
      "name": "python3",
      "display_name": "Python 3"
    },
    "language_info": {
      "name": "python"
    }
  },
  "cells": [
    {
      "cell_type": "markdown",
      "metadata": {
        "id": "view-in-github",
        "colab_type": "text"
      },
      "source": [
        "<a href=\"https://colab.research.google.com/github/Heisnotanimposter/CWorkspace/blob/main/LR_Parser_0331.c\" target=\"_parent\"><img src=\"https://colab.research.google.com/assets/colab-badge.svg\" alt=\"Open In Colab\"/></a>"
      ]
    },
    {
      "cell_type": "code",
      "execution_count": 1,
      "metadata": {
        "colab": {
          "base_uri": "https://localhost:8080/",
          "height": 110
        },
        "id": "Y52idE9Hcy81",
        "outputId": "71f71ac6-1d0a-4677-a5d9-fe5591ada512"
      },
      "outputs": [
        {
          "output_type": "error",
          "ename": "SyntaxError",
          "evalue": "invalid syntax (<ipython-input-1-75082bd5a678>, line 5)",
          "traceback": [
            "\u001b[0;36m  File \u001b[0;32m\"<ipython-input-1-75082bd5a678>\"\u001b[0;36m, line \u001b[0;32m5\u001b[0m\n\u001b[0;31m    int action_tbl[12][6] = {\u001b[0m\n\u001b[0m        ^\u001b[0m\n\u001b[0;31mSyntaxError\u001b[0m\u001b[0;31m:\u001b[0m invalid syntax\n"
          ]
        }
      ],
      "source": [
        "#include <stdio.h>\n",
        "#include <string.h>\n",
        "#include <stdlib.h>\n",
        "\n",
        "#define MAX 100\n",
        "int action_tbl[12][6] = {\n",
        "    { 5, 0, 0, 4, 0, 0 },\n",
        "    { 0, 6, 0, 0, 0, 999 },\n",
        "    { 0, -2, 7, 0, -2, -2 },\n",
        "    { 0, -4, -4, 0, -4, -4 },\n",
        "    { 5, 0, 0, 4, 0, 0 },\n",
        "    { 0, -6, -6, 0, -6, -6},\n",
        "    { 5, 0, 0, 4, 0, 0 },\n",
        "    { 5, 0, 0, 4, 0, 0 },\n",
        "    { 0, 6, 0, 0, 11, 0 },\n",
        "    { 0, -1, 7, 0, -1, -1 },\n",
        "    { 0, -3, -3, 0, -3, -3 },\n",
        "    { 0, -5, -5, 0, -5, -5 }\n",
        "};\n",
        "int goto_tbl[12][4] = {\n",
        "    { 0, 1, 2, 3 },\n",
        "    { 0, 0, 0, 0 },\n",
        "    { 0, 0, 0, 0 },\n",
        "    { 0, 0, 0, 0 },\n",
        "    { 0, 8, 2, 3 },\n",
        "    { 0, 0, 0, 0 },\n",
        "    { 0, 0, 9, 3 },\n",
        "    { 0, 0, 0, 10 },\n",
        "    { 0, 0, 0, 0 },\n",
        "    { 0, 0, 0, 0 },\n",
        "    { 0, 0, 0, 0 },\n",
        "    { 0, 0, 0, 0 }\n",
        "};\n",
        "\n",
        "\n",
        "// Stack for the parser state\n",
        "int stack[MAX], sp = -1;\n",
        "\n",
        "// Left-hand sides of the grammar's production rules\n",
        "char lhs[] = { ' ', 'E', 'E', 'T', 'T', 'F', 'F' };\n",
        "\n",
        "// Lengths of the right-hand sides of the grammar's production rules\n",
        "int rhs_len[] = { 0, 3, 1, 3, 1, 3, 1 };\n",
        "\n",
        "// Valid tokens in the grammar\n",
        "char token[] = { 'd', '+', '*', '(', ')', '$' };\n",
        "\n",
        "// Non-terminal symbols in the grammar\n",
        "char NT[] = { ' ', 'E', 'T', 'F' };\n",
        "\n",
        "// Function to push a value onto the stack\n",
        "void push(int stack[], int *sp, int value) {\n",
        "    if (*sp < MAX - 1) {\n",
        "        stack[++(*sp)] = value;\n",
        "    } else {\n",
        "        fprintf(stderr, \"Stack overflow\\n\");\n",
        "        exit(EXIT_FAILURE);\n",
        "    }\n",
        "}\n",
        "\n",
        "// Function to pop a value from the stack\n",
        "int pop(int stack[], int *sp) {\n",
        "    if (*sp >= 0) {\n",
        "        return stack[(*sp)--];\n",
        "    } else {\n",
        "        fprintf(stderr, \"Stack underflow\\n\");\n",
        "        exit(EXIT_FAILURE);\n",
        "    }\n",
        "}\n",
        "\n",
        "// Function to get the column index in the action table for a given token\n",
        "int get_token_index(char token_char) {\n",
        "    int num_tokens = sizeof(token) / sizeof(token[0]);\n",
        "    for (int i = 0; i < num_tokens; i++) {\n",
        "        if (token[i] == token_char) {\n",
        "            return i;\n",
        "        }\n",
        "    }\n",
        "    return -1; // Return -1 if the token is not found\n",
        "}\n",
        "\n",
        "void LR_Parser(char *input) {\n",
        "    int i, action, len_input, state;\n",
        "    char current_token;\n",
        "    sp = 0;\n",
        "    stack[0] = 0;\n",
        "    len_input = strlen(input);\n",
        "    input[len_input] = '$';\n",
        "    input[len_input + 1] = '\\0';\n",
        "\n",
        "    for (i = 0; i <= len_input;) {\n",
        "        current_token = input[i];\n",
        "        int token_index = get_token_index(current_token);\n",
        "        if (token_index == -1) {\n",
        "            printf(\"Syntax error: Invalid token.\\n\");\n",
        "            return;\n",
        "        }\n",
        "\n",
        "        state = stack[sp];\n",
        "        action = action_tbl[state][token_index];\n",
        "\n",
        "        if (action > 0) {\n",
        "\n",
        "            push(stack, &sp, action);\n",
        "            i++;\n",
        "        } else if (action < 0) {\n",
        "\n",
        "            int rule = -action;\n",
        "            sp -= rhs_len[rule];\n",
        "            state = stack[sp];\n",
        "            push(stack, &sp, goto_tbl[state][lhs[rule] - 'E']);\n",
        "\n",
        "        } else if (action == 999) {\n",
        "            printf(\"Parsing successful.\\n\");\n",
        "            return;\n",
        "        } else {\n",
        "            printf(\"Syntax error.\\n\");\n",
        "            return;\n",
        "        }\n",
        "    }\n",
        "}\n",
        "\n",
        "int main() {\n",
        "    char input[MAX];\n",
        "    printf(\"Enter a string to parse followed by a $ sign (e.g., d+d*$):\\n\");\n",
        "    while (fgets(input, MAX, stdin)) {\n",
        "        // Remove the newline character if it's present\n",
        "        input[strcspn(input, \"\\n\")] = '\\0';\n",
        "        if (input[0] == '$') {\n",
        "            break;\n",
        "        }\n",
        "        LR_Parser(input);\n",
        "        printf(\"Enter a string to parse followed by a $ sign (e.g., d+d*$):\\n\");\n",
        "    }\n",
        "    return 0;\n",
        "}"
      ]
    }
  ]
}