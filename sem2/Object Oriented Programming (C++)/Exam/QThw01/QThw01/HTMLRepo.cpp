#include "HTMLRepo.h"
#include <fstream>
#include <algorithm>
#include "CSVFileRepo.h"

void HTMLRepo::head()
{
	std::ofstream file{ this->fileName };
	if (file.is_open()) {
		file << "<!DOCTYPE html>" << std::endl;
		file << "<html>" << std::endl;
		file << "<head>" << std::endl;
		file << "	<title>ShoppingList</title>" << std::endl;
		file << "	<style>" << std::endl;
		file << "body {" << std::endl;
		file << "	font-family: Arial, sans-serif;" << std::endl;
		file << "	background: #f9f9f9;" << std::endl;
		file << "	margin: 20px;" << std::endl;
		file << "}" << std::endl;
		file << ".container {" << std::endl;
		file << "	display: flex;" << std::endl;
		file << "	flex-direction: column;" << std::endl;
		file << "	gap: 20px;" << std::endl;
		file << "	max-width: 600px;" << std::endl;
		file << "	margin: auto;" << std::endl;
		file << "}" << std::endl;
		file << ".item{" << std::endl;
		file << "	display: flex;" << std::endl;
		file << "	align-items: center;" << std::endl;
		file << "	background: white;" << std::endl;
		file << "	padding: 15px;" << std::endl;
		file << "	border-radius: 8px;" << std::endl;
		file << "	box-shadow: 0 2px 6px rgba(0, 0, 0, 0.1);" << std::endl;
		file << "}" << std::endl;
		file << ".item img {" << std::endl;
		file << "	width: 150px;" << std::endl;
		file << "	height: auto;" << std::endl;
		file << "	border-radius: 5px;" << std::endl;
		file << "	margin-right: 20px;" << std::endl;
		file << "}" << std::endl;
		file << ".info {" << std::endl;
		file << "	display: flex;" << std::endl;
		file << "	flex-direction: column;" << std::endl;
		file << "	gap: 5px;" << std::endl;
		file << "}" << std::endl;
		file << ".info span{" << std::endl;
		file << "	font-size: 14px;" << std::endl;
		file << "}" << std::endl;
		file << ".info .color {" << std::endl;
		file << "	font-weight: bold;" << std::endl;
		file << "	text-transform: capitalize;" << std::endl;
		file << "}" << std::endl;
		file << "</style>" << std::endl;
		file << "</head>" << std::endl;
	}
	else throw std::runtime_error("Could not open file: " + this->fileName);
}

void HTMLRepo::body()
{
	std::ofstream file;
	file.open(this->fileName, std::ios::app);
	if (file.is_open()) {
		file << "<body>" << std::endl;
		file << "<h1 style=\"text-align: center;\">Shopping List </h1>" << std::endl;
		file << "<div class=\"container\">" << std::endl;
	}
	else throw std::runtime_error("Invalid HTML file");
}

void HTMLRepo::end()
{
	std::ofstream file;
	file.open(this->fileName, std::ios::app);
	if (file.is_open()) {
		file << "</div>" << std::endl;
		file << "</body>" << std::endl;
		file << "</html>";
	}
	else throw std::runtime_error("Invalid HTML file");
}

HTMLRepo::HTMLRepo(const std::string fileName)
{
	this->fileName = fileName;

}

void HTMLRepo::openFileInChosenFormat()
{
	// create html file and open it in browser
	std::string newFileName = "html.html";
	std::ofstream file(newFileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + newFileName);
	}
	
	this->head();
	this->body();
	for (const auto& event : this->events) {
		file << "<div class=\"item\">" << std::endl;
		file << "	<img src=\"" << event.getLink() << "\" alt=\"" << event.getTitle() << "\">" << std::endl;
		file << "	<div class=\"info\">" << std::endl;
		file << "		<span class=\"color\">Title: </span>" << event.getTitle() << "<br>" << std::endl;
		file << "		<span class=\"color\">Description: </span>" << event.getDescription() << "<br>" << std::endl;
		file << "		<span class=\"color\">Date and Time: </span>" << event.getDateTime() << "<br>" << std::endl;
		file << "		<span class=\"color\">Number of People: </span>" << event.getNumberOfPeople() << "<br>" << std::endl;
		file << "	</div>" << std::endl;
		file << "</div>" << std::endl;
	}
	this->end();
	file.close();

	// Now open the file with the default browser
	std::string command = "start ./" + newFileName;
	int result = std::system(command.c_str());
}
