# DICE

**

![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![Standard](https://img.shields.io/badge/standard-C%2B%2B20-informational)
![GitHub repo size](https://img.shields.io/github/repo-size/qx1ls-dr/DICE)
# MVP

- Загрузка 2D-сцены из JSON.
- Рендеринг слоев.
- Перетаскивание одной фишки мышью.
- Ограничение перемещения фишки границами поля
- Базовая система триггеров для простейших игр.
- Взаимодействие с 2D компонентами: бросок кубика, перемещение фишек.


# Статус проекта







# Скриншоты





# Установка

## Бинарники
_TODO_

## Сборка с репозитория

### Linux

Клонирование репозитория.
```bash
git clone https://github.com/qx1ls-dr/DICE.git
```
Cборка проекта.
```
cd DICE
cmake . -B build
cd build
make
```
Запуск приложения.
```
./dice
```

### Windows
Планируется.

# Создание карты


# Команда
 - [Artur Yumashev](https://github.com/Ariumashev) 
 - [Leonid Diakov](https://github.com/qx1ls-dr)
 - [Yaroslav Ilyin](https://github.com/ilinyar2007-bit)

[![Arthur](https://img.shields.io/badge/Arthur-@STDWRK-2CA5E0?style=for-the-badge&logo=telegram)](https://t.me/StdWrk)
[![Leonid](https://img.shields.io/badge/Leonid-@xQyll1-3DDC84?style=for-the-badge&logo=telegram)](https://t.me/@xQyll1)
[![Yaroslav](https://img.shields.io/badge/Yaroslav-@Krudsoadayu-F59E0B?style=for-the-badge&logo=telegram)](https://t.me/@Krudsoadayu)
# Используемые библиотеки






[![Contributors](https://img.shields.io/github/contributors/qx1ls-dr/DICE.svg?style=for-the-badge)](https://github.com/qx1ls-dr/DICE/graphs/contributors)
[![Forks](https://img.shields.io/github/forks/qx1ls-dr/DICE.svg?style=for-the-badge)](https://github.com/qx1ls-dr/DICE/network/members)
[![Stargazers](https://img.shields.io/github/stars/qx1ls-dr/DICE.svg?style=for-the-badge)](https://github.com/qx1ls-dr/DICE/stargazers)
[![Issues](https://img.shields.io/github/issues/qx1ls-dr/DICE.svg?style=for-the-badge)](https://github.com/qx1ls-dr/DICE/issues)
[![License](https://img.shields.io/github/license/qx1ls-dr/DICE.svg?style=for-the-badge)](https://github.com/qx1ls-dr/DICE/blob/main/LICENSE)

![GitHub last commit](https://img.shields.io/github/last-commit/qx1ls-dr/DICE?style=for-the-badge)
![GitHub issues](https://img.shields.io/github/issues/qx1ls-dr/DICE?style=for-the-badge)
![GitHub pull requests](https://img.shields.io/github/issues-pr/qx1ls-dr/DICE?style=for-the-badge)

![CI](https://img.shields.io/github/actions/workflow/status/qx1ls-dr/DICE/ci-checks.yml?style=for-the-badge)
![Build](https://img.shields.io/github/actions/workflow/status/qx1ls-dr/DICE/cmake-single-platform.yml?style=for-the-badge)
![CodeQL](https://img.shields.io/github/actions/workflow/status/qx1ls-dr/DICE/codeql.yml?style=for-the-badge)

[![CodeFactor](https://img.shields.io/codefactor/grade/github/qx1ls-dr/DICE?style=for-the-badge)](https://www.codefactor.io/repository/github/qx1ls-dr/DICE)
[![Codacy Badge](https://img.shields.io/codacy/grade/DICE?style=for-the-badge)](https://app.codacy.com/gh/qx1ls-dr/DICE)


<br />
<div align="center">
  <h3 align="center">DICE</h3>

  <p align="center">
    Кинь игральный кубик и создай настольную игру своей мечты
    <br />
    &middot;
    <a href="https://github.com/qx1ls-dr/DICE/issues/new?labels=bug&template=bug-report---.md">Написать о баге</a>
    &middot;
    <a href="https://github.com/qx1ls-dr/DICE/issues/new?labels=enhancement&template=feature-request---.md">Предложить фичу</a>
    &middot;
  </p>
</div>


##  О проекте

DICE - это комплексный инструмент разработки настольных 2D-игр, написанный на С++. Система строится на принципе отделения игровой логики от графического представления, что позволяет пользователю создавать новые игры через конфигурационные файлы без пересборки всего приложения.



### Зависимости

В нашем проекте использовались:


[![SFML](https://img.shields.io/badge/SFML-Game%20Framework-8CC445?style=for-the-badge&logo=cplusplus)](https://www.sfml-dev.org/documentation/)

[![Lua](https://img.shields.io/badge/Lua-5.3-2C2D72?style=for-the-badge&logo=lua)](https://www.lua.org/manual/5.3/)

[![Dear ImGui](https://img.shields.io/badge/Dear%20ImGui-UI%20Library-1E1E1E?style=for-the-badge&logo=github)](https://github.com/ocornut/imgui)

[![nlohmann/json](https://img.shields.io/badge/nlohmann%2Fjson-JSON%20for%20C%2B%2B-000000?style=for-the-badge&logo=json)](https://json.nlohmann.me/)

[![sol2](https://img.shields.io/badge/sol2-Lua%20Bindings-000000?style=for-the-badge&logo=lua)](https://sol2.readthedocs.io/)


## Установка

1. Склонируйте репозиторий
   ```sh
   git clone https://github.com/qx1ls-dr/DICE.git
   ```
2. Перейдите в каталог DICE и пропишите
   ```sh
   cmake . -B build
   cd build
   make
   ```
4. Запустите приложение
   ```sh
    ./dice
   ```



<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] Add Changelog
- [x] Add back to top links
- [ ] Add Additional Templates w/ Examples
- [ ] Add "components" document to easily copy & paste sections of the readme
- [ ] Multi-language Support
    - [ ] Chinese
    - [ ] Spanish

See the [open issues](https://github.com/othneildrew/Best-README-Template/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Top contributors:

<a href="https://github.com/othneildrew/Best-README-Template/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=othneildrew/Best-README-Template" alt="contrib.rocks image" />
</a>

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the Unlicense License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Your Name - [@your_twitter](https://twitter.com/your_username) - email@example.com

Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. I've included a few of my favorites to kick things off!

* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Malven's Flexbox Cheatsheet](https://flexbox.malven.co/)
* [Malven's Grid Cheatsheet](https://grid.malven.co/)
* [Img Shields](https://shields.io)
* [GitHub Pages](https://pages.github.com)
* [Font Awesome](https://fontawesome.com)
* [React Icons](https://react-icons.github.io/react-icons/search)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
