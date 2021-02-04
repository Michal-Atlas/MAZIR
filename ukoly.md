# Úkoly

1. Nastudujte si, co je heap (managed vs. unmanaged).
2. Nastudujte si pointery.
3. Odstrante z programu, který jste dostali všechny memory leaks. (hint: valgrind)
4. Zjistěte, co je to garbage collection (připravte si otázky, co vám není jasné).
5. Metoda reference counting se nepoužívá pouze při GC. Např. C++ obsahuje chytré pointery, které umí počítat reference a free[^1] volá automaticky. Kdybychom je použili, bylo by potřeba stále volat free?
6. Řekněme, že bychom chtěli mít proceduru createSequenceInLinkedList(), která by vrátila linkedList, ve kterém by byla čísla 1 až 100. Proč tento kód nefunguje? Opravte ho.

```c
LinkedList* createSequenceInLInkedList() {
    LinkedList linkedList;
    init(&linkedList);
    for(int i = 1; i <= 100; i++) {
        append(&linkedList);
    }
    return &linkedList;
}
```

7. Přečtěte si v [Průvodci](pruvodce.ucw.cz) kapitoly 2.1, 2.2 a 2.3.
8. Opravte program, aby všechny procedury (samozřejmě kromě print) běžely v O(1) čase.
9. Přečtěte si v Průvodci kapitolu 4.1.
10. Přidejte procedury, aby se náš spojový seznam uměl chovat jako množina (stačí obyčejná).
11. Přečtěte si v Průvodci 8.1.
12. Napište binární vyhledávací strom (ne nutně vyvážený), který se bude chovat jako slovník. Jazyk použijte libovolný. Testovací vstup dodám.

S kódem, který jste dostali, můžete dělat, co chcete. Můžete ho libovolně modifikovat. Pokud se vám něco nelíbí, klidně to přepište a udělejte jinak. Mým kódem se vůbec neomezujte. Slouží spíše pro demonstraci, jak se používají pointery, a jako určitý základ, abyste nezačínali na zelené louce.

[^1] Ve skutečnosti nevolá free, ale delete. Delete před uvolněním paměti (free) ještě zavolá na objekt destruktor.
