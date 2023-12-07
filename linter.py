# -*- coding: utf-8 -*-
"""
    We have to comply with the demands of the teacher(s) in order to get the best possible grade,
    hence this verification script
"""
import sys
import os
import glob

# Workflow settings
EXIT_STATUS_SUCCESS = 0
EXIT_STATUS_FAILURE = 1

# Default settings
DEFAULT_RULER = 100


def print_error(line_num, message) -> None:
    print(f"\tLigne {line_num + 1:>3}: {message}")


def verify_ruler(lines: list[str], ruler: int) -> bool:
    success_status = EXIT_STATUS_SUCCESS

    for index, line in enumerate(lines):
        line_lenght = len(line)

        if line_lenght > ruler:
            success_status = EXIT_STATUS_FAILURE
            print_error(index, f"Ligne trop longue ({line_lenght} > {ruler}).")

    return success_status


def verify_constants(lines: list[str], file_extension: str) -> bool:
    success_status = EXIT_STATUS_SUCCESS
    c_file_extensions = ("c", "h")

    if file_extension in c_file_extensions:
        for index, line in enumerate(lines):
            if line.startswith("#define"):
                constant_name = line.split()[1].strip()

                # Verification de la constante en majuscules
                if not constant_name.isupper():
                    print_error(
                        index,
                        f"La constante `{constant_name}` contient au moins une minuscule."
                    )
                    success_status = EXIT_STATUS_FAILURE

                # Verification du commentaire de la constante
                if not constant_name.endswith('_H_') and '//' not in line:
                    print_error(index, f"La constante `{constant_name}` n'a pas de commentaire.")
                    success_status = EXIT_STATUS_FAILURE

    return success_status



def verify_header_comment(lines: list[str]) -> bool:
    return EXIT_STATUS_FAILURE if not lines[0].startswith("/") else EXIT_STATUS_SUCCESS

def verify_comment_spacing(lines: list[str], file_extension: str) -> bool:
    success_status = EXIT_STATUS_SUCCESS
    c_file_extensions = ("c", "h")

    if file_extension in c_file_extensions:
        for index in range(1, len(lines) - 1):
            if lines[index].startswith('/**'):
                previous_line_valid = lines[index - 1] == '\n' or lines[index - 1].startswith('/*')
                next_line_valid = lines[index + 1] == '\n' or lines[index + 1].startswith('/*')

                if not (previous_line_valid and next_line_valid):
                    print_error(index, f"Mauvaise aeration de la separation")
                    success_status = EXIT_STATUS_FAILURE

    return success_status


def main(files: list[list]) -> bool:
    exit_status = EXIT_STATUS_SUCCESS

    for filename in files:
        if not os.path.exists(filename):
            print(f"Fichier introuvable : {filename}")
            raise FileNotFoundError

        # Ouverture et traitement du fichier
        print(f'Ouverture de "{filename}":')
        with open(filename, "r") as f:
            lines = f.readlines()
            file_extension = filename.split(".")[-1]

            if verify_comment_spacing(lines, file_extension) == EXIT_STATUS_FAILURE:
                exit_status = EXIT_STATUS_FAILURE

            if verify_header_comment(lines) == EXIT_STATUS_FAILURE:
                exit_status = EXIT_STATUS_FAILURE

            if verify_ruler(lines, DEFAULT_RULER) == EXIT_STATUS_FAILURE:
                exit_status = EXIT_STATUS_FAILURE

            if verify_constants(lines, file_extension) == EXIT_STATUS_FAILURE:
                exit_status = EXIT_STATUS_FAILURE

        print(f'Fermeture de "{filename}".\n')

    return exit_status


if __name__ == "__main__":
    if len(sys.argv) != 2:
        script_name = os.path.splitext(os.path.basename(__file__))[0]
        print(f"Utilisation: python {script_name}.py file(s)")
        exit(EXIT_STATUS_FAILURE)

    file_patterns = sys.argv[1:]
    files = []

    for pattern in file_patterns:
        # Utilisation de glob pour trouver les fichiers correspondants au motif
        matching_files = glob.glob(pattern)
        files.extend(matching_files)

    if not files:
        print("Aucun fichier correspondant trouve.")
        exit(EXIT_STATUS_FAILURE)

    exit_status = main(files)
    exit(exit_status)
